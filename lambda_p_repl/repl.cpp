#include "repl.h"

#include <iostream>
#include <string>
#include <sstream>

#include <boost/bind.hpp>

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
	::std::wstring input;
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
	lexer.reset ();
	parser.reset ();
	while (!routines.routines->empty ())
	{
		routines.routines->pop_back ();
	}
}

void lambda_p_repl::repl::use_routine ()
{
}
		
void lambda_p_repl::repl::token_sink (::lambda_p::tokens::token * token)
{
	parser (token);
}