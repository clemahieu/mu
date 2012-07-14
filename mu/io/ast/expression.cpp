#include <mu/io/ast/expression.h>

#include <mu/io/ast/visitor.h>
#include <mu/io/ast/identifier.h>

mu::io::ast::expression::expression (mu::io::debugging::context context_a, std::vector <mu::io::ast::node *> values_a)
	: mu::io::ast::node (context_a),
	values (values_a),
	full_name (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring ()))
{
}

mu::io::ast::expression::expression (mu::io::debugging::context context_a, std::vector <mu::io::ast::node *> values_a, std::vector <mu::io::ast::identifier *> individual_names_a)
	: mu::io::ast::node (context_a),
	values (values_a),
	individual_names (individual_names_a),
	full_name (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring ()))
{
}

mu::io::ast::expression::expression (mu::io::debugging::context context_a, std::vector <mu::io::ast::node *> values_a, std::vector <mu::io::ast::identifier *> individual_names_a, mu::io::ast::identifier * full_name_a)
	: mu::io::ast::node (context_a),
    values (values_a),
	individual_names (individual_names_a),
	full_name (full_name_a)
{
}

std::wstring mu::io::ast::expression::name ()
{
	return std::wstring (L"expression");
}

void mu::io::ast::expression::operator () (mu::io::ast::visitor * visitor_a)
{
	(*visitor_a) (this);
}