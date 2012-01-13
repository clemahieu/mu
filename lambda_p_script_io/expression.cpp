#include "expression.h"

#include <lambda_p_script/expression.h>
#include <lambda_p_script/call.h>
#include <lambda_p/reference.h>
#include <lambda_p_script/reference.h>
#include <lambda_p_script/constant.h>
#include <lambda_p/expression.h>
#include <lambda_p/reference.h>

lambda_p_script_io::expression::expression (std::map <boost::shared_ptr <lambda_p::expression>, size_t> & reservations_a, boost::shared_ptr <lambda_p_script::call> call_a, boost::shared_ptr <lambda_p::node> node_a)
	: node (node_a),
	reservations (reservations_a),
	call_m (call_a)
{
	(*node_a) (this);
}

void lambda_p_script_io::expression::operator () (lambda_p::expression * expression_a)
{
	auto value (boost::static_pointer_cast <lambda_p::expression> (node));
	auto existing (reservations.find (value));
	assert (existing != reservations.end ());
	call_m->arguments.push_back (boost::shared_ptr <lambda_p_script::expression> (new lambda_p_script::expression (existing->second)));
}

void lambda_p_script_io::expression::operator () (lambda_p::reference * reference_a)
{
	auto value (boost::static_pointer_cast <lambda_p::reference> (node));
	auto existing (reservations.find (value->expression));
	assert (existing != reservations.end ());
	call_m->arguments.push_back (boost::shared_ptr <lambda_p_script::reference> (new lambda_p_script::reference (existing->second, value->index)));
}

void lambda_p_script_io::expression::operator () (lambda_p::node * node_a)
{
	auto value (boost::static_pointer_cast <lambda_p::node> (node));
	call_m->arguments.push_back (boost::shared_ptr <lambda_p_script::constant> (new lambda_p_script::constant (value)));
}