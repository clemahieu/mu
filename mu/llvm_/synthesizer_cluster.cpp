#include <mu/llvm_/synthesizer_cluster.h>

#include <mu/llvm_/synthesizer_routine.h>
#include <mu/llvm_/cluster/node.h>
#include <mu/llvm_/ast_cluster.h>

#include <gc_cpp.h>

mu::llvm_::synthesizer::cluster::cluster (mu::core::errors::error_target & errors_a, mu::llvm_::ast::cluster * cluster_a):
cluster_m (new (GC) mu::llvm_::cluster::node)
{
    for (auto i (cluster_a->routines.begin ()), j (cluster_a->routines.end ()); i != j; ++i)
    {
        mu::llvm_::synthesizer::routine routine (errors_a, *i);
        cluster_m->routines.push_back (routine.routine_m);
    }
}