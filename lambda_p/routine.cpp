#include "routine.h"

#include <lambda_p/pipe.h>
#include <lambda_p/entry.h>

lambda_p::routine::routine (boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: output (new lambda_p::pipe),
	errors (errors_a),
	input (new lambda_p::entry (errors_a))
{
}

lambda_p::routine::routine (boost::shared_ptr <lambda_p::entry> input_a, boost::shared_ptr <lambda_p::pipe> output_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: output (output_a),
	errors (errors_a),
	input (input_a)
{
	assert (output.get () != nullptr);
	assert (input.get () != nullptr);
}
