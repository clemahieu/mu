#include <mu/llvm_/cluster_to_extensions.h>

#include <mu/core/check.h>
#include <mu/script/context.h>
#include <mu/llvm_/cluster_node.h>
#include <mu/script/extensions_node.h>
#include <mu/io/keywording_extensions.h>
#include <mu/llvm_/function_node.h>

#include <gc_cpp.h>

bool mu::llvm_::cluster::to_extensions::operator () (mu::script::context & context_a)
{
    bool valid (mu::core::check <mu::llvm_::cluster::node> (context_a));
    if (valid)
    {
        auto cluster (static_cast <mu::llvm_::cluster::node *> (context_a.parameters(0)));
        auto result (new (GC) mu::script::extensions::node);
        for (auto i (cluster->routines.begin ()), j (cluster->routines.end ()); i != j; ++i)
        {
            auto error ((*result->extensions) (i->first, i->second));
            assert (!error);
        }
        context_a.push (result);
    }
    return valid;
}