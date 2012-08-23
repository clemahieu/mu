#include <mu/script/synthesizer_cluster.h>

#include <mu/script/synthesizer_routine.h>
#include <mu/script/cluster/node.h>
#include <mu/script/ast_cluster.h>

#include <gc_cpp.h>

mu::script::synthesizer::cluster::cluster (mu::core::errors::error_target & errors_a, mu::script::ast::cluster * cluster_a):
cluster_m (new (GC) mu::script::cluster::node)
{
    for (auto i (cluster_a->routines.begin ()), j (cluster_a->routines.end ()); i != j; ++i)
    {
        mu::script::synthesizer::routine routine (errors_a, *i);
        cluster_m->routines.push_back (routine.routine_m);
    }
}