#include "parameters.h"
#include <lambda_p_io/tokens/visitor.h>

std::wstring lambda_p_io::tokens::parameters::token_name ()
{
	return std::wstring (L"parameters");
}

void lambda_p_io::tokens::parameters::operator () (lambda_p_io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}