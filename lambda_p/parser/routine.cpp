#include <lambda_p/parser/routine.h>

#include <lambda_p/core/routine.h>

lambda_p::parser::routine::routine(void)
	: parsed_routine (false),
	routine_m (new ::lambda_p::core::routine)
{
}

lambda_p::parser::routine::~routine(void)
{
}

::lambda_p::parser::state_id lambda_p::parser::routine::state_type ()
{
	return ::lambda_p::parser::state_routine;
}