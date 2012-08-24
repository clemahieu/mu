#include <mu/llvm_/synthesizer_cluster.h>

#include <mu/llvm_/synthesizer_routine.h>
#include <mu/llvm_/cluster/node.h>
#include <mu/llvm_/ast_cluster.h>
#include <mu/llvm_/module/node.h>
#include <mu/llvm_/context/node.h>

#include <llvm/Module.h>

#include <gc_cpp.h>

mu::llvm_::synthesizer::cluster::cluster (mu::llvm_::context::node * context_a, mu::core::errors::error_target & errors_a, mu::llvm_::ast::cluster * cluster_a):
cluster_m (new (GC) mu::llvm_::cluster::node (new (GC) mu::llvm_::module::node (new llvm::Module ("", *context_a->context))))
{
    for (auto i (cluster_a->routines.begin ()), j (cluster_a->routines.end ()); i != j; ++i)
    {
        auto existing (routines.find (*i));
        if (existing == routines.end ())
        {
            mu::llvm_::synthesizer::routine routine (*this, context_a, cluster_m->module, errors_a, *i);
            cluster_m->routines.push_back (routine.routine_m);
        }
        else
        {
            cluster_m->routines.push_back (existing->second);
        }
    }
}