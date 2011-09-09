#include <lambda_p/lexer/whitespace.h>

lambda_p::lexer::whitespace::whitespace(void)
{
}

lambda_p::lexer::whitespace::~whitespace(void)
{
}

::lambda_p::lexer::state_id lambda_p::lexer::whitespace::state_type ()
{
	return ::lambda_p::lexer::state_whitespace;
}