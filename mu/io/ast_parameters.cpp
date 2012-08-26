#include <mu/io/ast_parameters.h>

#include <mu/io/ast_visitor.h>

mu::io::ast::parameters::parameters (mu::io::context context_a):
mu::io::ast::node (context_a)
{
}

mu::string mu::io::ast::parameters::name ()
{
	return mu::string (U"parameters");
}

void mu::io::ast::parameters::operator () (mu::io::ast::visitor * visitor_a)
{
	(*visitor_a) (this);
}