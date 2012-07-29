#include <mu/io/ast/builder.h>

#include <boost/bind.hpp>

#include <mu/script/ast/extension.h>
#include <mu/io/ast/cluster.h>
#include <mu/io/ast/node.h>
#include <mu/io/ast/expression.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/keywording/extensions.h>

#include <gc_cpp.h>

mu::io::ast::builder::builder ()
	: parser (errors, boost::bind (&mu::io::ast::builder::add, this, _1)),
    keywording (errors, [this] (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) { parser (token_a, context_a); }, new (GC) mu::io::keywording::extensions),
    lexer (errors, [this] (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) {keywording (token_a, context_a);}),
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