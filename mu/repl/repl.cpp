#include <mu/repl/repl.h>

#include <iostream>
#include <string>
#include <sstream>

#include <boost/bind.hpp>
#include <mu/core/errors/error_list.h>
#include <mu/core/errors/error.h>
#include <mu/repl/cli_stream.h>
#include <mu/io/source.h>
#include <mu/io/lexer_error.h>
#include <mu/repl/quit/operation.h>
#include <mu/script/print_operation.h>
#include <mu/script/context.h>
#include <mu/script/builder.h>
#include <mu/script/parser_scope_node.h>
#include <mu/io/lexer_stream_input.h>
#include <mu/core/types.h>
#include <mu/io/analyzer_extensions.h>
#include <mu/script/cluster_node.h>
#include <mu/script/runtime_routine.h>
#include <mu/script/parser_scope_merge.h>
#include <mu/repl/api.h>

#include <gc_cpp.h>

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
    auto core (mu::repl::api::core (*this));
	mu::script::builder builder (core);
    std::wstring line;
    std::getline (std::wcin, line);
    mu::string text;
    text.append (U"[--repl-routine-- [] [");
    text.append (line.begin (), line.end ());
    text.append (U"]]");
    mu::io::process (builder, text);
	if (builder.errors.errors.empty ())
	{
		if (builder.clusters.size () == 1)
		{
			auto cluster (builder.clusters [0]);
			if (cluster->routines.size () > 0)
			{
                mu::core::errors::error_list errors;
				mu::script::context ctx (errors);
				ctx.push (cluster->routines [U"--repl-routine--"]);
				auto valid (ctx ());
				if (valid)
				{
					ctx.slide ();
					ctx.push (new (GC) mu::script::print::operation);
					ctx.push (ctx.locals_begin (), ctx.locals_end ());
					auto valid (ctx ());
                    assert (valid);
				}
				else
				{
                    mu::stringstream stream;
					errors.print (stream);
                    mu::string const & string (stream.str ());
                    std::wstring wstring (string.begin (), string.end ());
                    std::wcout << wstring << std::endl;
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
        std::wcout << L"Error\n";
        mu::stringstream stream;
		builder.errors.print (stream);
        mu::string const & str (stream.str ());
        std::wstring string (str.begin (), str.end ());
        std::wcout << string;    
        std::wcout << L'\n';
	}
}