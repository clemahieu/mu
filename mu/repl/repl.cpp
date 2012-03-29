#include <mu/repl/repl.h>

#include <iostream>
#include <string>
#include <sstream>

#include <boost/bind.hpp>
#include <mu/core/errors/error_list.h>
#include <mu/core/errors/error.h>
#include <mu/repl/cli_stream.h>
#include <mu/io/source.h>
#include <mu/io/lexer/error.h>
#include <mu/io/parser/error.h>
#include <mu/repl/quit/operation.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/print/operation.h>
#include <mu/io/tokens/left_square.h>
#include <mu/io/tokens/right_square.h>
#include <mu/script/context.h>
#include <mu/io/builder.h>
#include <mu/script/extensions/node.h>
#include <mu/script/api.h>
#include <mu/core/routine.h>
#include <mu/io/debugging/stream.h>

#include <boost/make_shared.hpp>

mu::repl::repl::repl ()
	: stop_m (false)
{
}

void mu::repl::repl::reset ()
{
	stop_m = false;
}

void mu::repl::repl::run ()
{
	run_loop ();
	std::cout << "Exiting";
}

void mu::repl::repl::run_loop ()
{
	while (!stop_m)
	{
		iteration ();
	}
}

void mu::repl::repl::stop ()
{
	stop_m = true;
}

void mu::repl::repl::iteration ()
{
	std::wcout << L"mu> ";
	boost::shared_ptr <mu::io::lexer::character_stream> stream (new mu::repl::cli_stream (std::wcin));
	mu::io::builder builder (boost::shared_ptr <mu::script::extensions::node> (mu::script::api::core ())->extensions);
	auto quit (boost::shared_ptr <mu::core::node> (new mu::repl::quit::operation (*this)));
	builder.analyzer.extensions->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"quit"), boost::shared_ptr <mu::io::analyzer::extensions::extension> (new mu::io::analyzer::extensions::global (quit))));
	builder.parser (new mu::io::tokens::left_square (), mu::io::debugging::context ());
	builder (stream);
	builder (L']');
	builder ();
	if (builder.errors->errors.empty ())
	{
		if (builder.cluster != nullptr)
		{
			auto cluster (builder.cluster);
			if (cluster->routines.size () > 0)
			{
				mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
				mu::script::context ctx (errors);
				ctx.push (cluster->routines [0]);
				auto valid (ctx ());
				if (valid)
				{
					ctx.slide ();
					ctx.push (boost::make_shared <mu::script::print::operation> ());
					ctx.push (ctx.locals_begin (), ctx.locals_end ());
					auto valid (ctx ());
                    assert (valid);
				}
				else
				{
					errors.target->print (std::wcout);
				}
			}
			else
			{
				std::wcout << L"Cluster does not have a routine: ";
				std::wcout << cluster->routines.size ();
			}
		}
		else
		{
			std::wcout << L"Input was not a cluster";
		}
	}
	else
	{
		builder.errors->print (std::wcout);
	}
}