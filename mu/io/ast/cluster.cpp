#include <mu/io/ast/cluster.h>

#include <mu/io/ast/visitor.h>
#include <mu/io/debugging/stream.h>

mu::io::ast::cluster::cluster ()
	: mu::io::ast::node (mu::io::debugging::context ()),
	stream (new mu::io::debugging::stream)
{
}

mu::io::ast::cluster::cluster (mu::io::debugging::context context_a)
	: mu::io::ast::node (context_a),
	stream (new mu::io::debugging::stream)
{
}

void mu::io::ast::cluster::operator () (mu::io::ast::visitor * visitor_a)
{
	(*visitor_a) (this);
}

std::wstring mu::io::ast::cluster::name ()
{
	return std::wstring (L"cluster");
}