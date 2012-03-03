#include "tokens.right_square.h"
#include <mu/io/tokens.visitor.h>

std::wstring mu::io::tokens::right_square::token_name ()
{
	return std::wstring (L"right square");
}

void mu::io::tokens::right_square::operator () (mu::io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}
