#include "identifier_state.h"

lambda_p::serialization::lexer::identifier_state::identifier_state(void)
{
}

lambda_p::serialization::lexer::identifier_state::~identifier_state(void)
{
}

::lambda_p::serialization::lexer::state_id lambda_p::serialization::lexer::identifier_state::state_type ()
{
	return ::lambda_p::serialization::lexer::state_identifier;
}
