#include <mu/io/ast/cluster.h>

#include <mu/io/ast/visitor.h>

mu::io::ast::cluster::cluster ():
mu::io::ast::node (mu::io::context ())
{
}

mu::io::ast::cluster::cluster (mu::io::context context_a):
mu::io::ast::node (context_a)
{
}

void mu::io::ast::cluster::operator () (mu::io::ast::visitor * visitor_a)
{
	(*visitor_a) (this);
}

mu::string mu::io::ast::cluster::name ()
{
	return mu::string (U"cluster");
}