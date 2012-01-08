#include "routine.h"

#include <lambda_p_script/runtime/routine.h>
#include <lambda_p_script/synthesizer/synthesizer.h>
#include <lambda_p_script/synthesizer/expression.h>
#include <lambda_p/routine.h>
#include <lambda_p_script/synthesizer/order.h>

lambda_p_script::synthesizer::routine::routine (lambda_p_script::synthesizer::synthesizer & synthesizer_a, boost::shared_ptr <lambda_p::routine> routine_a)
	: result (new lambda_p_script::runtime::routine),
	open (0)
{	
	auto expression (boost::shared_ptr <lambda_p_script::synthesizer::expression> (new lambda_p_script::synthesizer::expression (*this, routine_a->call)));
	for (auto i (expressions.begin ()), j (expressions.end ()); i != j; ++i)
	{
		(*(*i)) ();
	}
}
			
void lambda_p_script::synthesizer::routine::operator () (boost::shared_ptr <lambda_p_script::synthesizer::order> expression, boost::shared_ptr <lambda_p::call> call)
{
	expressions.push_front (expression);
	synthesis.insert (std::map <boost::shared_ptr <lambda_p::call>, std::list <boost::shared_ptr <lambda_p_script::synthesizer::expression>>::iterator>::value_type (call, expressions.begin ()));
}

void lambda_p_script::synthesizer::routine::operator () (boost::shared_ptr <lambda_p::call> dominator, boost::shared_ptr <lambda_p::call> follower)
{
	auto existing_dominator (synthesis.find (dominator));
	auto existing_follower (synthesis.find (follower));
	assert (existing_dominator != synthesis.end ());
	assert (existing_follower != synthesis.end ());
	++existing_dominator;
	synthesis.erase (existing_follower);
	synthesis.insert (existing_dominator, follower);
}