#include "synthesizer.h"

#include <lambda_p_script_io/order.h>
#include <lambda_p/routine.h>
#include <lambda_p_script_io/generator.h>

lambda_p_script_io::synthesizer::synthesizer (boost::function <void (boost::shared_ptr <lambda_p_script::routine>)> target_a)
	: target (target_a)
{
}

void lambda_p_script_io::synthesizer::operator () (boost::shared_ptr <lambda_p::routine> routine_a)
{
	lambda_p_script_io::order order (routine_a->call);
	lambda_p_script_io::generator generator (order.expressions, routine_a->parameters);
	target (generator.result);
}
