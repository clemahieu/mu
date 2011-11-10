#include "repl.h"

#include <iostream>
#include <string>
#include <sstream>

#include <boost/bind.hpp>

#include <lambda_p_repl/entry_routine.h>
#include <lambda_p/lexer/wistream_input.h>

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
	lambda_p::lexer::wistream_input input (std::wcin);
	boost::shared_ptr <lambda_p::lexer::character_stream> stream (new lambda_p::lexer::wistream_input (input));
	lambda_p_repl::entry_routine routine (this, stream, std::wcout);
	routine ();
}
