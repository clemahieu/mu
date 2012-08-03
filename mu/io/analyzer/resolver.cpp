#include <mu/io/analyzer/resolver.h>

#include <mu/core/expression.h>
#include <mu/core/errors/error_target.h>

mu::io::analyzer::resolver::resolver (boost::function <void (mu::core::node *)> unresolved_a, mu::io::debugging::context const & context_a):
unresolved (unresolved_a),
context(context_a),
only_global (false)
{
}

void mu::io::analyzer::resolver::operator () (mu::core::errors::error_target & errors, bool global, mu::io::debugging::context const & context_a, mu::core::node * node_a)
{
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
        unresolved (node_a);
    }
}