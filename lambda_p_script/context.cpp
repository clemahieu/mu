#include "context.h"

lambda_p_script::context::context (boost::shared_ptr <lambda_p_script::cluster::node> cluster_a, boost::shared_ptr <lambda_p::node> parameters_a, size_t size)
	: nodes (size),
	parameters (parameters_a),
	cluster (cluster_a)
{
}