#include <mu/script/cluster_to_parser_scope.h>

#include <mu/core/check.h>
#include <mu/script/context.h>
#include <mu/script/cluster_node.h>
#include <mu/script/parser_scope_node.h>
#include <mu/io/analyzer_extensions.h>
#include <mu/script/runtime_routine.h>

#include <gc_cpp.h>

bool mu::script::cluster::to_parser_scope::operator () (mu::script::context & context_a)
{
    bool valid (mu::core::check <mu::script::cluster::node> (context_a));
    if (valid)
    {
        auto cluster (static_cast <mu::script::cluster::node *> (context_a.parameters(0)));
        auto result (new (GC) mu::script::parser_scope::node);
        for (auto i (cluster->routines.begin ()), j (cluster->routines.end ()); i != j; ++i)
        {
            result->injected [i->first] = i->second;
        }
        context_a.push (result);
    }
    return valid;
}