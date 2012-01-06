#include "parameters.h"

#include <lambda_p_io/ast/visitor.h>

std::wstring lambda_p_io::ast::parameters::name ()
{
	return std::wstring (L"parameters");
}

void lambda_p_io::ast::parameters::operator () (lambda_p_io::ast::visitor * visitor_a)
{
	(*visitor_a) (this);
}