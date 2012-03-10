#include <mu/script/runtime/frame.h>

mu::script::runtime::frame::frame (boost::shared_ptr <mu::script::cluster::node> cluster_a, boost::shared_ptr <mu::core::node> parameters_a, size_t size)
	: parameters (parameters_a),
	cluster (cluster_a),
	nodes (size)
{
}