#include <lambda_p_serialization/tokens/identifier.h>
#include <lambda_p_serialization/tokens/visitor.h>

lambda_p_serialization::tokens::identifier::identifier (std::wstring string_a)
	: string (string_a)
{
}

std::wstring lambda_p_serialization::tokens::identifier::token_name ()
{
	return std::wstring (L"identifier");
}

void lambda_p_serialization::tokens::identifier::operator () (lambda_p_serialization::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}