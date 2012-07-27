#include <mu/io/analyzer/resolver.h>

#include <mu/core/expression.h>
#include <mu/core/errors/error_target.h>

mu::io::analyzer::resolver::resolver (mu::core::expression & unresolved_a, size_t position_a, mu::io::debugging::context const & context_a)
	: unresolved (unresolved_a),
    context(context_a),
	position (position_a),
    only_global (false)
{
	assert (unresolved_a.dependencies [position_a] == nullptr);
}

void mu::io::analyzer::resolver::operator () (mu::core::errors::error_target & errors, bool global, mu::io::debugging::context const & context_a, mu::core::node * node_a)
{
	assert (unresolved.dependencies [position] == nullptr);
    if (only_global && !global)
    {
        mu::stringstream message;
        message << U"Reference at: ";
        message << context.string ();
        message << U" cannot be resolved by local declaration at: ";
        message << context_a.string ();
        errors (message.str ());
    }
    else
    {
        unresolved.dependencies [position] = node_a;
    }
}