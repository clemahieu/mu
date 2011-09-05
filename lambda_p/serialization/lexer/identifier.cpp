#include "identifier.h"

lambda_p::serialization::lexer::identifier::identifier(void)
{
}

lambda_p::serialization::lexer::identifier::~identifier(void)
{
}

::lambda_p::serialization::lexer::state_id lambda_p::serialization::lexer::identifier::state_type ()
{
	return ::lambda_p::serialization::lexer::state_id::state_identifier;
}
