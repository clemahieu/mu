#include "error_state.h"

lambda_p::serialization::lexer::error_state::error_state(::std::wstring message_a)
	: message (message_a)
{
}

lambda_p::serialization::lexer::error_state::~error_state(void)
{
}

::lambda_p::serialization::lexer::state_id lambda_p::serialization::lexer::error_state::state_type ()
{
	return ::lambda_p::serialization::lexer::state_error;
}