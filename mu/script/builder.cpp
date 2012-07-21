#include <mu/script/builder.h>

#include <boost/bind.hpp>

#include <mu/script/ast/extension.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/ast/cluster.h>
#include <mu/io/ast/node.h>
#include <mu/io/ast/expression.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/context.h>
#include <mu/script/synthesizer/operation.h>
#include <mu/script/cluster/node.h>

#include <gc_cpp.h>

mu::script::builder::builder ()
	: errors (new (GC) mu::core::errors::error_list),
	analyzer (boost::bind (&mu::script::builder::add, this, _1), errors),
	parser (errors, boost::bind (&mu::io::analyzer::analyzer::input, &analyzer, _1)),
	lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2)),
    cluster (nullptr)
{
}

mu::script::builder::builder (mu::io::analyzer::extensions::extensions * extensions_a)
	: errors (new (GC) mu::core::errors::error_list),
	analyzer (boost::bind (&mu::script::builder::add, this, _1), errors, extensions_a),
	parser (errors, boost::bind (&mu::io::analyzer::analyzer::input, &analyzer, _1)),
	lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2)),
    cluster(nullptr)
{
}

void mu::script::builder::add (mu::core::cluster * cluster_a)
{
	assert (cluster == nullptr);
    mu::core::errors::errors errors_l (errors);
    mu::script::context context (errors_l);
    context.push (new (GC) mu::script::synthesizer::operation);
    context.push (cluster_a);
    auto valid (context ());
    assert (valid);
    assert (context.working_size () == 1);
    assert (dynamic_cast <mu::script::cluster::node *> (context.working (0)) != nullptr);
    cluster = static_cast <mu::script::cluster::node *> (context.working (0));
}

void mu::script::builder::operator () (mu::io::lexer::context const & context_a)
{
	assert (cluster == nullptr);
	lexer (context_a);
}