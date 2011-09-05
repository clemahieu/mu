#include "error.h"

lambda_p::serialization::lexer::error::error(::std::wstring message_a)
	: message (message_a)
{
}

lambda_p::serialization::lexer::error::~error(void)
{
}

::lambda_p::serialization::lexer::state_id lambda_p::serialization::lexer::error::state_type ()
{
	return ::lambda_p::serialization::lexer::state_error;
}