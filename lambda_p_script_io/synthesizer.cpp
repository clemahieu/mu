#include "synthesizer.h"

#include <lambda_p/order.h>
#include <lambda_p/routine.h>
#include <lambda_p_script_io/generator.h>
#include <lambda_p_script/routine.h>

void lambda_p_script_io::synthesizer::operator() (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p::routine> (parameters [0]));
	if (one.get () != nullptr)
	{
		lambda_p::order order (one->body, one->parameters);
		lambda_p_script_io::generator generator (order.expressions, one->parameters);
		results.push_back (generator.result);
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_script_io::synthesizer::count ()
{
	return 1;
}