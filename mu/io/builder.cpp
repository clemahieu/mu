#include <mu/io/builder.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <mu/script/ast/extension.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/ast/cluster.h>
#include <mu/io/ast/node.h>
#include <mu/io/ast/expression.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/debugging/stream.h>

mu::io::builder::builder ()
	: errors (new mu::core::errors::error_list),
	analyzer (boost::bind (&mu::io::builder::add, this, _1), errors),
	parser (errors, boost::bind (&mu::io::analyzer::analyzer::input, &analyzer, _1)),
	lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2))
{
}

mu::io::builder::builder (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a)
	: errors (new mu::core::errors::error_list),
	analyzer (boost::bind (&mu::io::builder::add, this, _1), errors, extensions_a),
	parser (errors, boost::bind (&mu::io::analyzer::analyzer::input, &analyzer, _1)),
	lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2))
{
}

void mu::io::builder::add (boost::shared_ptr <mu::core::cluster> cluster_a)
{
	assert (cluster == nullptr);
	cluster =  cluster_a;
}

void mu::io::builder::operator () (wchar_t char_a)
{
	assert (cluster == nullptr);
	lexer (char_a);
}