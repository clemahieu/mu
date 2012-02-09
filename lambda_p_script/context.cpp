#include "context.h"

lambda_p_script::context::context (boost::shared_ptr <lambda_p_script::remapping> remapping_a, boost::shared_ptr <lambda_p::node> parameters_a, size_t size)
	: nodes (size),
	parameters (parameters_a),
	remapping (remapping_a)
{
}