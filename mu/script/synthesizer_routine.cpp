#include <mu/script/synthesizer_routine.h>

#include <mu/script/runtime/routine.h>
#include <mu/script/synthesizer_expression.h>
#include <mu/script/ast_routine.h>
#include <mu/script/synthesizer_cluster.h>

#include <gc_cpp.h>

#include <assert.h>

mu::script::synthesizer::routine::routine (mu::core::errors::error_target & errors_a, mu::script::synthesizer::cluster & cluster_a, mu::script::ast::routine * routine_a):
errors (errors_a),
routine_m (new (GC) mu::script::runtime::routine),
cluster (cluster_a)
{
    assert (cluster_a.routines.find (routine_a) == cluster_a.routines.end ());
    cluster_a.routines [routine_a] = routine_m;
    mu::script::synthesizer::expression expression (*this, routine_a->body);
}