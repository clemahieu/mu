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
#include <mu/script/synthesizer/operationd.h>
#include <mu/script/cluster/node.h>
#include <mu/io/debugging/mapping.h>
#include <mu/io/debugging/stream.h>

mu::script::builder::builder (boost::shared_ptr <mu::io::debugging::stream> stream_a)
	: errors (new mu::core::errors::error_list),
	analyzer (boost::bind (&mu::script::builder::add, this, _1, _2), errors, stream_a),
	parser (errors, boost::bind (&mu::io::analyzer::analyzer::input, &analyzer, _1)),
	stream (new mu::io::debugging::stream),
	lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2))
{
}

mu::script::builder::builder (boost::shared_ptr <mu::io::debugging::stream> stream_a, boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a)
	: errors (new mu::core::errors::error_list),
	analyzer (boost::bind (&mu::script::builder::add, this, _1, _2), errors, extensions_a, stream_a),
	parser (errors, boost::bind (&mu::io::analyzer::analyzer::input, &analyzer, _1)),
	stream (new mu::io::debugging::stream),
	lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2))
{
}

void mu::script::builder::add (boost::shared_ptr <mu::core::cluster> cluster_a, boost::shared_ptr <mu::io::debugging::mapping> cluster_info_a)
{
	assert (cluster == nullptr);
	assert (cluster_info == nullptr);
    mu::core::errors::errors errors_l (errors);
    mu::script::context context (errors_l);
    context.push (boost::make_shared <mu::script::synthesizer::operationd> ());
    context.push (cluster_a);
	context.push (cluster_info_a);
    auto valid (context ());
    assert (valid);
    assert (context.working_size () == 2);
    assert (boost::dynamic_pointer_cast <mu::script::cluster::node> (context.working (0)).get () != nullptr);
    cluster = boost::static_pointer_cast <mu::script::cluster::node> (context.working (0));
	assert (boost::dynamic_pointer_cast <mu::io::debugging::mapping> (context.working (1)) != nullptr);
	cluster_info = boost::static_pointer_cast <mu::io::debugging::mapping> (context.working (1));
}

void mu::script::builder::operator () (wchar_t char_a)
{
	assert (cluster == nullptr);
	assert (cluster_info == nullptr);
	lexer (char_a);
}