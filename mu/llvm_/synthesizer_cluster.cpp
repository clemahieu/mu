#include <mu/llvm_/synthesizer_cluster.h>

#include <mu/llvm_/synthesizer_routine.h>
#include <mu/llvm_/cluster_node.h>
#include <mu/llvm_/ast_cluster.h>
#include <mu/llvm_/module_node.h>
#include <mu/llvm_/context_node.h>
#include <mu/llvm_/ast_routine.h>

#include <llvm/Module.h>

#include <gc_cpp.h>

mu::llvm_::synthesizer::cluster::cluster (mu::llvm_::context::node * context_a, mu::core::errors::error_target & errors_a, mu::llvm_::ast::cluster * cluster_a):
cluster_m (new (GC) mu::llvm_::cluster::node (new (GC) mu::llvm_::module::node (new llvm::Module ("", *context_a->context))))
{
    for (auto i (cluster_a->routines.begin ()), j (cluster_a->routines.end ()); i != j; ++i)
    {
        auto existing (routines.find (*i));
        assert (cluster_m->routines.find ((*i)->name) == cluster_m->routines.end ());
        if (existing == routines.end ())
        {
            mu::llvm_::synthesizer::routine routine (*this, context_a, cluster_m->module, errors_a, *i);
            cluster_m->routines [(*i)->name] = routine.routine_m;
        }
        else
        {
            cluster_m->routines [(*i)->name] = existing->second;
        }
    }
}