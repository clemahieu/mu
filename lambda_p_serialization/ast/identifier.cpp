#include "identifier.h"

#include <lambda_p_serialization/ast/visitor.h>

lambda_p_serialization::ast::identifier::identifier (std::wstring string_a)
	: string (string_a)
{
}

std::wstring lambda_p_serialization::ast::identifier::name ()
{
	return std::wstring (L"identifier");
}

void lambda_p_serialization::ast::identifier::operator () (lambda_p_serialization::ast::visitor * visitor_a)
{
	(*visitor_a) (this);
}