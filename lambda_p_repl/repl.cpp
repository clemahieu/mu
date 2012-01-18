#include "repl.h"

#include <iostream>
#include <string>
#include <sstream>

#include <boost/bind.hpp>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/errors/error.h>
#include <lambda_p_repl/cli_stream.h>
#include <lambda_p_script_io/builder.h>
#include <lambda_p_io/source.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_io/lexer/error.h>
#include <lambda_p_io/parser/error.h>
#include <lambda_p_repl/quit/operation.h>
#include <lambda_p_io/analyzer/extensions/global.h>
#include <lambda_p_llvm/api.h>

lambda_p_repl::repl::repl(void)
	: stop_m (false)
{
}

lambda_p_repl::repl::~repl(void)
{
}

void lambda_p_repl::repl::reset ()
{
	stop_m = false;
}

void lambda_p_repl::repl::run ()
{
	run_loop ();
	std::cout << "Exiting";
}

void lambda_p_repl::repl::run_loop ()
{
	while (!stop_m)
	{
		iteration ();
	}
}

void lambda_p_repl::repl::stop ()
{
	stop_m = true;
}

void lambda_p_repl::repl::iteration ()
{
	std::wcout << L"lp> ";
	boost::shared_ptr <lambda_p_io::lexer::character_stream> stream (new lambda_p_repl::cli_stream (std::wcin));
	lambda_p_script_io::builder builder;
	lambda_p_llvm::api api;
	builder.analyzer.extensions.insert (api.extensions.begin (), api.extensions.end ());
	auto quit (boost::shared_ptr <lambda_p::node> (new lambda_p_repl::quit::operation (*this)));
	builder.analyzer.extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L".quit"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (quit))));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (stream);
	source ();
	if (builder.errors->errors.empty () && ! builder.lexer.error () && !builder.parser.error ())
	{
		bool stop (false);
		for (auto i (builder.routines.begin ()), j (builder.routines.end ()); i != j && !stop; ++i)
		{
			auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
			std::vector <boost::shared_ptr <lambda_p::node>> arguments;
			std::vector <boost::shared_ptr <lambda_p::node>> results;
			auto routine (builder.routines [0]);
			routine->perform (errors, arguments, results);
			for (auto k (errors->errors.begin ()), l (errors->errors.end ()); k != l; ++k)
			{
				stop = true;
				(*k)->string (std::wcout);
				std::wcout << L"\n";
			}
			if (errors->errors.empty ())
			{
				for (auto k (results.begin ()), l (results.end ()); k != l; ++k)
				{
					std::wcout << (*k)->debug ();
					std::wcout << L" ";
				}
				std::wcout << L"\n";
			}
		}
	}
	else
	{
		if (builder.lexer.error ())
		{
			std::wcout << boost::static_pointer_cast <lambda_p_io::lexer::error> (builder.lexer.state.top ())->message;
			std::wcout << L"\n";
		}
		if (builder.parser.error ())
		{
			std::wcout << boost::static_pointer_cast <lambda_p_io::parser::error> (builder.parser.state.top ())->message;
			std::wcout << L"\n";
		}
		for (auto i (builder.errors->errors.begin ()), j (builder.errors->errors.end ()); i != j; ++i)
		{
			(*i)->string (std::wcout);
			std::wcout << L"\n";
		}
	}
}
