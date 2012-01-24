#include "parameters.h"

#include <lambda_p_io/ast/visitor.h>

lambda_p_io::ast::parameters::parameters (lambda_p::context context_a)
	: lambda_p_io::ast::node (context_a)
{
}

std::wstring lambda_p_io::ast::parameters::name ()
{
	return std::wstring (L"parameters");
}

void lambda_p_io::ast::parameters::operator () (lambda_p_io::ast::visitor * visitor_a)
{
	(*visitor_a) (this);
}