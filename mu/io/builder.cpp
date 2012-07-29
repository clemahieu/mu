#include <mu/io/builder.h>

#include <boost/bind.hpp>

#include <mu/script/ast/extension.h>
#include <mu/io/ast/cluster.h>
#include <mu/io/ast/node.h>
#include <mu/io/ast/expression.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/keywording/extensions.h>

#include <gc_cpp.h>

mu::io::builder::builder ()
	: analyzer (boost::bind (&mu::io::builder::add, this, _1), errors),
	parser (errors, boost::bind (&mu::io::analyzer::analyzer::input, &analyzer, _1)),
    keywording (errors, [this] (mu::io::tokens::token * token, mu::io::debugging::context context) {parser (token, context);}, new (GC) mu::io::keywording::extensions),
    lexer (errors, [this] (mu::io::tokens::token * token, mu::io::debugging::context context) {keywording (token, context); }),
    cluster (nullptr)
{
}

mu::io::builder::builder (mu::io::keywording::extensions * extensions_a)
	: analyzer (boost::bind (&mu::io::builder::add, this, _1), errors),
	parser (errors, boost::bind (&mu::io::analyzer::analyzer::input, &analyzer, _1)),
    keywording (errors, [this, extensions_a] (mu::io::tokens::token * token, mu::io::debugging::context context) {parser (token, context);}, extensions_a),
    lexer (errors, [this] (mu::io::tokens::token * token, mu::io::debugging::context context) {keywording (token, context); }),
    cluster (nullptr)
{
}

void mu::io::builder::add (mu::core::cluster * cluster_a)
{
	assert (cluster == nullptr);
	cluster =  cluster_a;
}

void mu::io::builder::operator () (mu::io::lexer::context const & context_a)
{
	assert (cluster == nullptr);
	lexer (context_a);
}