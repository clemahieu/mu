#include "quit_parameter.h"

#include <lambda_p_repl/repl.h>
#include <lambda_p/core/routine.h>

lambda_p_repl::quit_parameter::quit_parameter (::lambda_p_repl::repl & repl_a)
	: repl (repl_a)
{
}

lambda_p_repl::quit_parameter::~quit_parameter (void)
{
}

void ::lambda_p_repl::quit_parameter::apply_to (::lambda_p::core::routine * routine_a)
{
	repl.stop ();
}