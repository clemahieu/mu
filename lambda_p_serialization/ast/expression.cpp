#include "expression.h"

#include <lambda_p_serialization/ast/visitor.h>

std::wstring lambda_p_serialization::ast::expression::name ()
{
	return std::wstring (L"expression");
}

void lambda_p_serialization::ast::expression::operator () (lambda_p_serialization::ast::visitor * visitor_a)
{
	(*visitor_a) (this);
}