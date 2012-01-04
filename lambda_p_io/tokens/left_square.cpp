#include "left_square.h"
#include <lambda_p_io/tokens/visitor.h>

std::wstring lambda_p_io::tokens::left_square::token_name ()
{
	return std::wstring (L"left square");
}

void lambda_p_io::tokens::left_square::operator () (lambda_p_io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}