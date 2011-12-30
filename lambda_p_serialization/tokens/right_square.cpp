#include "right_square.h"
#include <lambda_p_serialization/tokens/visitor.h>

std::wstring lambda_p_serialization::tokens::right_square::token_name ()
{
	return std::wstring (L"right square");
}

void lambda_p_serialization::tokens::right_square::operator () (lambda_p_serialization::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}