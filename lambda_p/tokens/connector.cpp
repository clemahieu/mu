#include <lambda_p/tokens/connector.h>

lambda_p::tokens::connector::connector(void)
{
}

lambda_p::tokens::connector::~connector(void)
{
}

::lambda_p::tokens::token_ids lambda_p::tokens::connector::token_id ()
{
	return ::lambda_p::tokens::token_id_connector;
}