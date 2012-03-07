#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/visitor.h>

#include <iostream>

mu::io::tokens::identifier::identifier (std::wstring string_a)
	: string (string_a)
{
}

std::wstring mu::io::tokens::identifier::token_name ()
{
	return std::wstring (L"identifier");
}

void mu::io::tokens::identifier::operator () (mu::io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}