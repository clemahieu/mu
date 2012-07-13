#include <mu/script/builder.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

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
	lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2))
{
}

mu::script::builder::builder (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a)
	: errors (new (GC) mu::core::errors::error_list),
	analyzer (boost::bind (&mu::script::builder::add, this, _1), errors, extensions_a),
	parser (errors, boost::bind (&mu::io::analyzer::analyzer::input, &analyzer, _1)),
	lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2))
{
}

void mu::script::builder::add (boost::shared_ptr <mu::core::cluster> cluster_a)
{
	assert (cluster == nullptr);
    mu::core::errors::errors errors_l (errors);
    mu::script::context context (errors_l);
    context.push (boost::make_shared <mu::script::synthesizer::operation> ());
    context.push (cluster_a);
    auto valid (context ());
    assert (valid);
    assert (context.working_size () == 1);
    assert (boost::dynamic_pointer_cast <mu::script::cluster::node> (context.working (0)).get () != nullptr);
    cluster = boost::static_pointer_cast <mu::script::cluster::node> (context.working (0));
}

void mu::script::builder::operator () (wchar_t char_a)
{
	assert (cluster == nullptr);
	lexer (char_a);
}