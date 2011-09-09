#include <lambda_p/lexer/identifier.h>

lambda_p::lexer::identifier::identifier(void)
{
}

lambda_p::lexer::identifier::~identifier(void)
{
}

::lambda_p::lexer::state_id lambda_p::lexer::identifier::state_type ()
{
	return ::lambda_p::lexer::state_identifier;
}
