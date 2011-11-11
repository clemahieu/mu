#include "repl.h"

#include <iostream>
#include <string>
#include <sstream>

#include <boost/bind.hpp>

#include <lambda_p/lexer/wistream_input.h>
#include <lambda_p_repl/entry_input.h>
#include <lambda_p_llvm/context.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_repl/api.h>
#include <lambda_p_repl/exec_binder.h>
#include <lambda_p_kernel/package.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p/errors/error.h>

#include <llvm/Module.h>

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
	lambda_p::lexer::wistream_input in (std::wcin);
	boost::shared_ptr <lambda_p::lexer::character_stream> stream (new lambda_p::lexer::wistream_input (in));
	lambda_p_repl::api api;
	boost::shared_ptr <lambda_p::binder::node> environment (api ());
	std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> injected_parameters;
	injected_parameters.push_back (std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>> (std::wstring (L"environment"), environment));	
	boost::shared_ptr <lambda_p_repl::exec_binder> exec_binder (new lambda_p_repl::exec_binder);
	exec_binder->set (environment, exec_binder);
	injected_parameters.push_back (std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>> (std::wstring (L"exec"), exec_binder));
	lambda_p_repl::entry_input input (environment, exec_binder);
    input (stream, std::wcout);
    if (input.routine.get () != nullptr)
    {
		lambda_p::errors::error_list problems;
		lambda_p_kernel::apply apply;
		lambda_p::binder::list nodes;
		lambda_p::binder::list declarations;
		apply.core (input.routine, nodes, problems, declarations);
		if (!problems.errors.empty ())
		{
			std::wcout << "Binding error:\n";
			std::wstringstream stream;
			for (auto i = problems.errors.begin (); i != problems.errors.end (); ++i)
			{
				(*i)->string (stream);
				stream << L'\n';
			}
			stream.seekg (0);
			std::wstring error (stream.str ());
			std::wcout << error;
			std::wcout << '\n';
		}
    }
}
