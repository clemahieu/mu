#include <mu/io/ast/builder.h>

#include <boost/bind.hpp>

#include <mu/script/ast/extension.h>
#include <mu/io/ast/cluster.h>
#include <mu/io/ast/node.h>
#include <mu/io/ast/expression.h>
#include <mu/core/errors/error_list.h>

#include <gc_cpp.h>

mu::io::ast::builder::builder ()
	: parser (errors, boost::bind (&mu::io::ast::builder::add, this, _1)),
	lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2)),
	cluster (new mu::io::ast::cluster)
{
}

void mu::io::ast::builder::add (mu::io::ast::cluster * node_a)
{
	cluster = node_a;
}

void mu::io::ast::builder::operator () (mu::io::lexer::context const & context_a)
{
	lexer (context_a);
}