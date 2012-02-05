#include "parameters.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_script/context.h>

#include <sstream>

void lambda_p_script::parameters::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::context & context, std::vector <boost::shared_ptr <lambda_p::node>> & target)
{
	target.push_back (context.parameters);
}