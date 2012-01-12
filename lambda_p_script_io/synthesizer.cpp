#include "synthesizer.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_script_io/routine.h>
#include <lambda_p_script/call.h>
#include <lambda_p_script/routine.h>
#include <lambda_p/call.h>
#include <lambda_p_script/constant.h>
#include <lambda_p_script/expression.h>
#include <lambda_p_script_io/generator.h>
#include <lambda_p/routine.h>

lambda_p_script_io::synthesizer::synthesizer (boost::function <void (boost::shared_ptr <lambda_p_script::routine>)> target_a)
	: target (target_a)
{
}

void lambda_p_script_io::synthesizer::operator () (boost::shared_ptr <lambda_p::routine> routine_a)
{
	lambda_p_script_io::routine routine (routine_a);
	lambda_p_script_io::generator generator (routine.expressions, routine_a->parameters);
	target (generator.result);
}