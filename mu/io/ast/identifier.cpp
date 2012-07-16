#include <mu/io/ast/identifier.h>

#include <mu/io/ast/visitor.h>

mu::io::ast::identifier::identifier (mu::io::debugging::context context_a, mu::string string_a)
	: mu::io::ast::node (context_a),
	string (string_a)
{
}

mu::string mu::io::ast::identifier::name ()
{
	return mu::string (U"identifier");
}

void mu::io::ast::identifier::operator () (mu::io::ast::visitor * visitor_a)
{
	(*visitor_a) (this);
}