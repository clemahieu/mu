#include <lambda_p_serialization/tokens/complex_identifier.h>

lambda_p_serialization::tokens::complex_identifier::complex_identifier (std::wstring identifier_a, std::wstring terminator_a)
	: identifier (identifier_a),
	terminator (terminator_a)
{
}

lambda_p_serialization::tokens::token_ids lambda_p_serialization::tokens::complex_identifier::token_id ()
{
	return lambda_p_serialization::tokens::token_id_complex_identifier;
}

std::wstring lambda_p_serialization::tokens::complex_identifier::token_name ()
{
	return std::wstring (L"complex identifier");
}