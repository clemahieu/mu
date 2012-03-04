#include <mu/script/runtime.context.h>

mu::script::runtime::context::context (boost::shared_ptr <mu::script::cluster::node> cluster_a, boost::shared_ptr <mu::core::node> parameters_a, size_t size)
	: nodes (size),
	parameters (parameters_a),
	cluster (cluster_a)
{
}
