#include <lambda_p_io/tokens/identifier.h>
#include <lambda_p_io/tokens/visitor.h>

lambda_p_io::tokens::identifier::identifier (std::wstring string_a)
	: string (string_a)
{
}

std::wstring lambda_p_io::tokens::identifier::token_name ()
{
	return std::wstring (L"identifier");
}

void lambda_p_io::tokens::identifier::operator () (lambda_p_io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}