#include "routine.h"

#include <lambda_p_script/routine.h>
#include <lambda_p_script_io/synthesizer.h>
#include <lambda_p_script_io/expression.h>
#include <lambda_p/routine.h>
#include <lambda_p/call.h>

lambda_p_script_io::routine::routine (lambda_p_script_io::synthesizer & synthesizer_a, boost::shared_ptr <lambda_p::routine> routine_a)
{	
	auto expression (boost::shared_ptr <lambda_p_script_io::expression> (new lambda_p_script_io::expression (*this, routine_a->call)));
}
			
void lambda_p_script_io::routine::operator () (boost::shared_ptr <lambda_p::call> expression)
{
	expressions.push_front (expression);
	synthesis.insert (std::map <boost::shared_ptr <lambda_p::call>, std::list <boost::shared_ptr <lambda_p::call>>::iterator>::value_type (expression, expressions.begin ()));
}

void lambda_p_script_io::routine::operator () (boost::shared_ptr <lambda_p::call> dominator, boost::shared_ptr <lambda_p::call> follower)
{
	auto existing_dominator (synthesis.find (dominator));
	auto existing_follower (synthesis.find (follower));
	assert (existing_dominator != synthesis.end ());
	assert (existing_follower != synthesis.end ());
	++existing_dominator;
	expressions.erase (existing_follower->second);
	expressions.insert (existing_dominator->second, follower);
}