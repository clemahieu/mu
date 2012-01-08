#include "order.h"

lambda_p_script::synthesizer::order::order (lambda_p_script::synthesizer::routine & routine_a, boost::shared_ptr <lambda_p::call> call_a)
	: call (call_a),
	routine (routine_a)
{
}

void lambda_p_script::synthesizer::order::operator () ()
{
}