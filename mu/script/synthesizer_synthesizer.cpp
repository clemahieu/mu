#include <mu/script/synthesizer_synthesizer.h>

#include <mu/script/synthesizer_cluster.h>

mu::script::synthesizer::synthesizer::synthesizer (mu::core::errors::error_target & errors_a, boost::function <void (mu::script::cluster::node *)> target_a):
target (target_a),
errors (errors_a)
{
}

void mu::script::synthesizer::synthesizer::operator () (mu::script::ast::cluster * cluster_a)
{
    mu::script::synthesizer::cluster cluster (errors, cluster_a);
    target (cluster.cluster_m);
}