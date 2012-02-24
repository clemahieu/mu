#include "left_square.h"
#include <io/tokens/visitor.h>

std::wstring mu::io::tokens::left_square::token_name ()
{
	return std::wstring (L"left square");
}

void mu::io::tokens::left_square::operator () (mu::io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}