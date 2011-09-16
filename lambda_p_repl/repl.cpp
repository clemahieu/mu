#include "repl.h"

#include <iostream>
#include <string>
#include <sstream>

#include <boost/bind.hpp>

#include <lambda_p/binder/routine_binder.h>
#include <lambda_p_repl/repl_quit_binder.h>
#include <lambda_p/binder/command_list.h>
#include <lambda_p_repl/hello_world_binder.h>
#include <lambda_p_repl/echo_binder.h>
#include <lambda_p/binder/structure.h>
#include <lambda_p_repl/routine_input.h>
#include <lambda_p/binder/data_to_string_binder.h>
#include <lambda_p_repl/entry_routine.h>

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
	::std::cout << "Exiting";
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
	::lambda_p_repl::routine_input input;
	::std::wstring environment (L"main\n ;! environment\n;;\n");
	input (environment);
	::std::wcout << environment;
	input (::std::wcin, ::std::wcout);
	if (input.error ())
	{
		::std::wcout << "Lexing error:\n";
		::std::wstring message;
		input.error_message (message);
		::std::wcout << message;
		::std::wcout << '\n';
	}
	else
	{
		::std::wcout << L">>\n";
        ::std::wstringstream stream;
		::boost::shared_ptr < ::lambda_p::core::routine> routine ((*input.routines.routines)[0]);
        routine->validate (stream);
        ::std::wstring errors (stream.str ());
        if (errors.empty ())
        {
            use_routine (routine);
        }
        else
        {
            ::std::wcout << "Validation error:\n";
            ::std::wcout << errors;
            ::std::wcout << '\n';
        }
	}
}

void lambda_p_repl::repl::use_routine (::boost::shared_ptr < ::lambda_p::core::routine> routine_a)
{	
	::lambda_p::binder::routine_binder routine_binder;
	::lambda_p_repl::entry_routine routine (routine_a);	
	::boost::shared_ptr < ::lambda_p_repl::repl_quit_binder> quit_binder (new ::lambda_p_repl::repl_quit_binder (routine.commands, *this));
	::std::wstring quit_name (L"quit");
	routine.dereference_binder->nodes [quit_name] = quit_binder;
	
	routine ();
}