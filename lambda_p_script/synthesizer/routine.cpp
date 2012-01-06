#include "routine.h"

#include <lambda_p_script/routine.h>
#include <lambda_p_script/synthesizer/synthesizer.h>
#include <lambda_p_script/synthesizer/expression.h>

lambda_p_script::synthesizer::routine::routine (lambda_p_script::synthesizer::synthesizer & synthesizer_a, boost::shared_ptr <lambda_p::expression> expression_a)
	: result (new lambda_p_script::routine)
{	
	lambda_p_script::synthesizer::expression expression (expression_a);
}

void lambda_p_script::synthesizer::routine::operator () (boost::shared_ptr <lambda_p::expression> dominator, boost::shared_ptr <lambda_p::expression> new_expression_a)
{
	auto existing (synthesis.find (dominator));
	assert (existing != synthesis.end ());
	++existing;
	synthesis.insert (existing, new_expression_a);
}