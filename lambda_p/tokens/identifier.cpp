#include <lambda_p/tokens/identifier.h>

lambda_p::tokens::identifier::identifier (std::wstring string_a)
	: string (string_a)
{
}

lambda_p::tokens::token_ids lambda_p::tokens::identifier::token_id ()
{
	return lambda_p::tokens::token_id_identifier;
}