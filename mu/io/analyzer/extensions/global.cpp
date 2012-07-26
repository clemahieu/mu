#include <mu/io/analyzer/extensions/global.h>

#include <mu/io/analyzer/expression.h>
#include <mu/core/expression.h>
#include <mu/io/ast/expression.h>

mu::io::analyzer::extensions::global::global (mu::core::node * node_a)
	: node (node_a)
{
}

void mu::io::analyzer::extensions::global::operator () (mu::core::errors::error_target & errors_a, mu::io::analyzer::expression & expression_a, mu::string remaining)
{
    assert (remaining.empty ());
	expression_a.self->dependencies.push_back (node);
}

bool mu::io::analyzer::extensions::global::operator () ()
{
    return false;
}