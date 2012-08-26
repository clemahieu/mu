#include <mu/io/analyzer_resolver.h>

#include <mu/core/errors/error_target.h>
#include <mu/core/node_list.h>

mu::io::analyzer::resolver::resolver (mu::core::node_list & target_a, mu::io::context const & context_a):
target (target_a),
context(context_a),
only_global (false)
{
}

auto mu::io::analyzer::resolver::operator () (mu::core::errors::error_target &errors, bool global, const mu::io::context &context_a, mu::core::node * node_a) -> void
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
            assert (target.nodes.size () == 0);
            target.nodes.push_back (node_a);
        }
    }