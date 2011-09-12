#include "repl.h"

#include <iostream>
#include <string>
#include <sstream>

#include <boost/bind.hpp>

#include <lambda_p/binder/routine_binder.h>
#include <lambda_p_repl/repl_quit_binder.h>
#include <lambda_p/binder/bound_routine.h>
#include <lambda_p_repl/hello_world_binder.h>

lambda_p_repl::repl::repl(void)
	: stop_m (false),
	parser (routines),
	lexer (::boost::bind (&::lambda_p_repl::repl::token_sink, this, _1))
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
	lexer.reset ();
	parser.reset ();
	while (!routines.routines->empty ())
	{
		routines.routines->pop_back ();
	}
	::std::wstring input;
	::std::wstring environment (L"main ;! quit ;! hello ;;\n");
	for (::std::wstring::const_iterator i = environment.begin (); i != environment.end (); ++i)
	{
		lexer (*i);
	}
	while (routines.routines->empty () && !lexer.error () && !parser.error ())
	{
		::std::wcout << L"lp> ";
		::std::getline (::std::wcin, input);
		input.push_back ('\n');
		for (::std::wstring::const_iterator i = input.begin (); i != input.end (); ++i)
		{
			lexer (*i);
		}
	}
	if (lexer.error ())
	{
		::std::wcout << "Lexing error:\n";
		::std::wstring message;
		lexer.error_message (message);
		::std::wcout << message;
		::std::wcout << '\n';
	}
	else if (parser.error ())
	{
		::std::wcout << "Parsing error:\n";
		::std::wstring message;
		parser.error_message (message);
		::std::wcout << message;
		::std::wcout << '\n';
	}
	else
	{
		::std::wcout << L">>\n";
		use_routine ();
	}
}

void lambda_p_repl::repl::use_routine ()
{
	::lambda_p::binder::routine_binder routine_binder;
	::boost::shared_ptr < ::lambda_p_repl::repl_quit_binder> quit_binder (new ::lambda_p_repl::repl_quit_binder (*this));
	routine_binder.instances [quit_node ()] = quit_binder;
	::boost::shared_ptr < ::lambda_p_repl::hello_world_binder> hello_binder (new ::lambda_p_repl::hello_world_binder);
	routine_binder.instances [hello_node ()] = hello_binder;
	routine_binder ((*routines.routines) [0]);
	if (routine_binder.error ())
	{
		::std::wcout << "Binding error:\n";
		::std::wstring message;
		routine_binder.error_message (message);
		::std::wcout << message;
		::std::wcout << '\n';
	}
	else
	{
		(*routine_binder.routine) ();
	}
}

::lambda_p::core::node * lambda_p_repl::repl::quit_node ()
{
	::lambda_p::core::node * result ((*routines.routines) [0]->statements [0]->arguments [0]);
	return result;
}

::lambda_p::core::node * lambda_p_repl::repl::hello_node ()
{
	::lambda_p::core::node * result ((*routines.routines) [0]->statements [0]->arguments [1]);
	return result;
}
		
void lambda_p_repl::repl::token_sink (::lambda_p::tokens::token * token)
{
	parser (token);
}