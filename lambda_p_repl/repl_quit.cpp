#include "repl_quit.h"

#include <lambda_p_repl/repl.h>
#include <lambda_p/core/routine.h>

lambda_p_repl::repl_quit::repl_quit (::lambda_p_repl::repl & repl_a)
	: repl (repl_a)
{
}

lambda_p_repl::repl_quit::~repl_quit (void)
{
}

void ::lambda_p_repl::repl_quit::operator () ()
{
	repl.stop ();
}