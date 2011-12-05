#include <lambda_p/tokens/complex_identifier.h>

lambda_p::tokens::complex_identifier::complex_identifier (std::wstring identifier_a, std::wstring terminator_a)
	: identifier (identifier_a),
	terminator (terminator_a)
{
}

lambda_p::tokens::token_ids lambda_p::tokens::complex_identifier::token_id ()
{
	return lambda_p::tokens::token_id_complex_identifier;
}

std::wstring lambda_p::tokens::complex_identifier::token_name ()
{
	return std::wstring (L"complex identifier");
}