#include "operation.h"

#include <lambda_p/errors/error_list.h>

#include <sstream>

void lambda_p_script::nodes::operation::execute (lambda_p_script::context & context, boost::shared_ptr <lambda_p::errors::error_list> errors_a, std::vector <size_t> parameter_locations, std::vector <size_t> result_locations)
{
	assert (parameter_locations.size () == parameter_count ());
	assert (result_locations.size () == result_count ());
	(*this) (context, errors_a, parameter_locations, result_locations);
}