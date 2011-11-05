#include "application.h"

lambda_p_kernel::application::application (boost::shared_ptr <lambda_p_kernel::routine> routine_a, boost::shared_ptr <lambda_p::binder::list> nodes_a)
	: routine (routine_a),
	nodes (nodes_a)
{
}
