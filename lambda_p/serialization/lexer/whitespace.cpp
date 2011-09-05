#include "whitespace.h"

lambda_p::serialization::lexer::whitespace::whitespace(void)
{
}

lambda_p::serialization::lexer::whitespace::~whitespace(void)
{
}

::lambda_p::serialization::lexer::state_id lambda_p::serialization::lexer::whitespace::state_type ()
{
	return ::lambda_p::serialization::lexer::state_id::state_whitespace;
}