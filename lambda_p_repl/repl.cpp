#include "repl.h"

#include <iostream>
#include <string>
#include <sstream>

#include <boost/bind.hpp>
#include <lambda_p_repl/api.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/errors/error.h>
#include <lambda_p_io/lexer/wistream_input.h>
#include <lambda_p_script_io/builder.h>
#include <lambda_p_io/source.h>
#include <lambda_p_script/routine.h>

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
	boost::shared_ptr <lambda_p_io::lexer::character_stream> stream (new lambda_p_io::lexer::wistream_input (std::wcin));
	lambda_p_repl::api api;
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (stream);
	if (builder.errors->errors.empty ())
	{
		for (auto i (builder.routines.begin ()), j (builder.routines.end ()); i != j; ++i)
		{
			auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
			std::vector <boost::shared_ptr <lambda_p::node>> arguments;
			std::vector <boost::shared_ptr <lambda_p::node>> results;
			auto routine (builder.routines [0]);
			routine->perform (errors, arguments, results);
			for (auto k (errors->errors.begin ()), l (errors->errors.end ()); k != l; ++k)
			{
				(*k)->string (std::wcout);
			}
		}
	}
}
