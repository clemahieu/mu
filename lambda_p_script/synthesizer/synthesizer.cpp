#include "synthesizer.h"

lambda_p_script::synthesizer::synthesizer (boost::function <void (boost::shared_ptr <lambda_p_script::routine>)> target_a)
	: target (target_a)
{
}

void lambda_p_script::synthesizer::operator () (boost::shared_ptr <lambda_p::expression> expression_a)
{

}