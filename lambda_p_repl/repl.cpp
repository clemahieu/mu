#include "repl.h"

#include <iostream>
#include <string>
#include <sstream>

#include <boost/bind.hpp>

#include <lambda_p_repl/entry_routine.h>
#include <lambda_p_repl/repl_quit.h>
#include <lambda_p_repl/entry_environment.h>

lambda_p_repl::repl::repl(void)
	: stop_m (false),
	quit (new ::lambda_p_repl::repl_quit (*this))
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
	::lambda_p_repl::entry_routine routine (quit, ::std::wcin, ::std::wcout);
	routine ();
}
