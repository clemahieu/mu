#include <mu/llvm_/synthesizer_synthesizer.h>

#include <mu/llvm_/synthesizer_cluster.h>

mu::llvm_::synthesizer::synthesizer::synthesizer (mu::llvm_::context::node * context_a, mu::core::errors::error_target & errors_a, boost::function <void (mu::llvm_::cluster::node *)> target_a):
target (target_a),
errors (errors_a),
context (context_a)
{
}

void mu::llvm_::synthesizer::synthesizer::operator () (mu::llvm_::ast::cluster * cluster_a)
{
    mu::llvm_::synthesizer::cluster cluster (context, errors, cluster_a);
    target (cluster.cluster_m);
}