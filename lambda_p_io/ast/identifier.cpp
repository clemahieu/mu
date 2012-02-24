#include "identifier.h"

#include <lambda_p_io/ast/visitor.h>

lambda_p_io::ast::identifier::identifier (mu::core::context context_a, std::wstring string_a)
	: string (string_a),
	lambda_p_io::ast::node (context_a)
{
}

std::wstring lambda_p_io::ast::identifier::name ()
{
	return std::wstring (L"identifier");
}

void lambda_p_io::ast::identifier::operator () (lambda_p_io::ast::visitor * visitor_a)
{
	(*visitor_a) (this);
}