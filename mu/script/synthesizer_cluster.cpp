#include <mu/script/synthesizer_cluster.h>

mu::script::synthesizer::cluster::cluster (boost::function <void (mu::script::cluster::node *)> target_a, mu::script::ast::cluster * cluster_a):
target (target_a),
cluster_m (cluster_a)
{
}