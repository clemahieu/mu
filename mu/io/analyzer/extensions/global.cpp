#include <mu/io/analyzer/extensions/global.h>

#include <mu/io/analyzer/expression.h>
#include <mu/core/expression.h>
#include <mu/io/ast/expression.h>

#include <boost/make_shared.hpp>

mu::io::analyzer::extensions::global::global (boost::shared_ptr <mu::core::node> node_a)
	: node (node_a)
{
}

void mu::io::analyzer::extensions::global::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a)
{
	expression_a.self->dependencies.push_back (node);
}