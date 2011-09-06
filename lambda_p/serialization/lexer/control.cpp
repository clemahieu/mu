#include <lambda_p/serialization/lexer/control.h>

lambda_p::serialization::lexer::control::control(void)
	: complete (false)
{
}

lambda_p::serialization::lexer::control::~control(void)
{
}

::lambda_p::serialization::lexer::state_id lambda_p::serialization::lexer::control::state_type ()
{
	return ::lambda_p::serialization::lexer::state_control;
}