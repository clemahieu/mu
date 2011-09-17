//
//  entry_input.cpp
//  lambda_p_repl
//
//  Created by Colin LeMahieu on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p_repl/entry_input.h>

#include <lambda_p_repl/routine_input.h>

#include <sstream>
#include <iostream>

void lambda_p_repl::entry_input::operator () (::std::wistream & in, ::std::wostream & out)
{
	::lambda_p_repl::routine_input input;
	::std::wstring environment (L"main\n ;= environment\n;;\n");
	input (environment);
	out << environment;
	input (in, out);
	if (input.error ())
	{
		out << "Lexing error:\n";
		::std::wstring message;
		input.error_message (message);
		out << message;
		out << '\n';
	}
	else if (input.routines.routines->size () < 1)
	{
		out << L"Input reached end of stream\n";
	}
	else
	{
		out << L">>\n";
        ::std::wstringstream stream;
		routine = (*input.routines.routines)[0];
        routine->validate (stream);
        ::std::wstring errors (stream.str ());
        if (!errors.empty ())
        {
            routine.reset ();
            out << "Validation error:\n";
            out << errors;
            out << '\n';
        }
	}
}