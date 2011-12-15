#include <lambda_p_serialization/tokens/identifier.h>

lambda_p_serialization::tokens::identifier::identifier (std::wstring string_a)
	: string (string_a)
{
}

lambda_p_serialization::tokens::token_ids lambda_p_serialization::tokens::identifier::token_id ()
{
	return lambda_p_serialization::tokens::token_id_identifier;
}

std::wstring lambda_p_serialization::tokens::identifier::token_name ()
{
	return std::wstring (L"identifier");
}