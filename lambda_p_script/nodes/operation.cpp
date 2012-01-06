#include "operation.h"

lambda_p_script::nodes::operation::operation (size_t parameter_size_a, size_t result_size_a, boost::shared_ptr <lambda_p_script::operation> operation_a)
	: parameter_size (parameter_size_a),
	result_size (result_size_a),
	operation (operation_a)
{
}