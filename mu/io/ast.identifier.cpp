#include "ast.identifier.h"

#include <mu/io/ast.visitor.h>

mu::io::ast::identifier::identifier (mu::core::context context_a, std::wstring string_a)
	: string (string_a),
	mu::io::ast::node (context_a)
{
}

std::wstring mu::io::ast::identifier::name ()
{
	return std::wstring (L"identifier");
}

void mu::io::ast::identifier::operator () (mu::io::ast::visitor * visitor_a)
{
	(*visitor_a) (this);
}
