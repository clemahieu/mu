#include "expression.h"

#include <lambda_p_script/synthesizer/routine.h>
#include <lambda_p/call.h>
#include <lambda_p/expression.h>
#include <lambda_p_script/synthesizer/order.h>

lambda_p_script::synthesizer::expression::expression (lambda_p_script::synthesizer::routine & routine_a, boost::shared_ptr <lambda_p::call> call_a)
	: routine (routine_a),
	order (new lambda_p_script::synthesizer::order (routine_a, call_a))
{
	routine (order, call_a);
	for (auto i (call_a->dependencies.begin ()), j (call_a->dependencies.end ()); i != j; ++i)
	{
		current = (*i);
		(*(*i)) (this);
	}
}

void lambda_p_script::synthesizer::expression::operator () (lambda_p::call * call_a)
{
	auto call_l (boost::static_pointer_cast <lambda_p::call> (current));
	auto existing (routine.synthesis.find (call_l));
	if (existing == routine.synthesis.end ())
	{
		auto expression (boost::shared_ptr <lambda_p_script::synthesizer::expression> (new lambda_p_script::synthesizer::expression (routine, call_l)));
	}
	routine (call_l, order->call);
}

void lambda_p_script::synthesizer::expression::operator () (lambda_p::parameters * parameters_a)
{
}

void lambda_p_script::synthesizer::expression::operator () (lambda_p::reference * reference_a)
{
}

void lambda_p_script::synthesizer::expression::operator () (lambda_p::node * node_a)
{
}