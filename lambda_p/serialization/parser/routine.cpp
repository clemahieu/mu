#include <lambda_p/serialization/parser/routine.h>

#include <lambda_p/core/routine.h>

lambda_p::serialization::parser::routine::routine(void)
	: parsed_routine (false),
	routine_m (new ::lambda_p::core::routine (0))
{
}

lambda_p::serialization::parser::routine::~routine(void)
{
}

::lambda_p::serialization::parser::state_id lambda_p::serialization::parser::routine::state_type ()
{
	return ::lambda_p::serialization::parser::state_routine;
}