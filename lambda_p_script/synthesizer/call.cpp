#include "call.h"

#include <lambda_p_script/synthesizer/routine.h>
#include <lambda_p_script/synthesizer/generator.h>
#include <lambda_p_script/runtime/expression.h>
#include <lambda_p_script/runtime/call.h>
#include <lambda_p/reference.h>
#include <lambda_p_script/runtime/reference.h>
#include <lambda_p_script/runtime/constant.h>
#include <lambda_p/call.h>
#include <lambda_p/parameters.h>
#include <lambda_p/reference.h>

lambda_p_script::synthesizer::call::call (lambda_p_script::synthesizer::generator & generator_a, boost::shared_ptr <lambda_p_script::runtime::call> call_a, boost::shared_ptr <lambda_p::node> node_a)
	: node (node_a),
	generator (generator_a),
	call_m (call_a)
{
}

void lambda_p_script::synthesizer::call::operator () (lambda_p::call * call_a)
{
	auto value (boost::static_pointer_cast <lambda_p::call> (node));
	auto existing (generator.reservation.find (value));
	assert (existing != generator.reservation.end ());
	call_m->arguments.push_back (boost::shared_ptr <lambda_p_script::runtime::expression> (new lambda_p_script::runtime::expression (existing->second)));
}

void lambda_p_script::synthesizer::call::operator () (lambda_p::parameters * parameters_a)
{
	auto value (boost::static_pointer_cast <lambda_p::parameters> (node));
	call_m->arguments.push_back (boost::shared_ptr <lambda_p_script::runtime::expression> (new lambda_p_script::runtime::expression (0)));
}

void lambda_p_script::synthesizer::call::operator () (lambda_p::reference * reference_a)
{
	auto value (boost::static_pointer_cast <lambda_p::reference> (node));
	auto existing (generator.reservation.find (value->call));
	assert (existing != generator.reservation.end ());
	call_m->arguments.push_back (boost::shared_ptr <lambda_p_script::runtime::reference> (new lambda_p_script::runtime::reference (existing->second, value->index)));
}

void lambda_p_script::synthesizer::call::operator () (lambda_p::node * node_a)
{
	auto value (boost::static_pointer_cast <lambda_p::node> (node));
	call_m->arguments.push_back (boost::shared_ptr <lambda_p_script::runtime::constant> (new lambda_p_script::runtime::constant (value)));
}