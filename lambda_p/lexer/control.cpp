#include <lambda_p/lexer/control.h>

lambda_p::lexer::control::control(void)
	: complete (false)
{
}

lambda_p::lexer::control::~control(void)
{
}

lambda_p::lexer::state_id lambda_p::lexer::control::state_type ()
{
	return lambda_p::lexer::state_control;
}