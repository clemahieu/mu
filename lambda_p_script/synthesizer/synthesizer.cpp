#include "synthesizer.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_script/synthesizer/routine.h>
#include <lambda_p_script/runtime/call.h>
#include <lambda_p_script/runtime/routine.h>
#include <lambda_p/call.h>
#include <lambda_p_script/runtime/constant.h>
#include <lambda_p_script/runtime/expression.h>
#include <lambda_p_script/synthesizer/generator.h>

lambda_p_script::synthesizer::synthesizer::synthesizer (boost::function <void (boost::shared_ptr <lambda_p_script::runtime::routine>)> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: target (target_a),
	errors (errors_a)
{
}

void lambda_p_script::synthesizer::synthesizer::operator () (boost::shared_ptr <lambda_p::routine> routine_a)
{
	lambda_p_script::synthesizer::routine routine (*this, routine_a);
	if (!(*errors) ())
	{
		lambda_p_script::synthesizer::generator generator (routine);
		target (generator.result);
	}
}