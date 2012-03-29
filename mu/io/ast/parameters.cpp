#include <mu/io/ast/parameters.h>

#include <mu/io/ast/visitor.h>

mu::io::ast::parameters::parameters (mu::io::debugging::context context_a)
	: mu::io::ast::node (context_a)
{
}

std::wstring mu::io::ast::parameters::name ()
{
	return std::wstring (L"parameters");
}

void mu::io::ast::parameters::operator () (mu::io::ast::visitor * visitor_a)
{
	(*visitor_a) (this);
}