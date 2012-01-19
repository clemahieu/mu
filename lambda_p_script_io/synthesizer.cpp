#include "synthesizer.h"

#include <lambda_p/order.h>
#include <lambda_p/routine.h>
#include <lambda_p_script_io/generator.h>

lambda_p_script_io::synthesizer::synthesizer (boost::function <void (boost::shared_ptr <lambda_p_script::routine>)> target_a)
	: target (target_a)
{
}

void lambda_p_script_io::synthesizer::operator () (boost::shared_ptr <lambda_p::routine> routine_a)
{
	lambda_p::order order (routine_a->body, routine_a->parameters);
	lambda_p_script_io::generator generator (order.expressions, routine_a->parameters);
	target (generator.result);
}
