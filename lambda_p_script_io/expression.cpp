#include "expression.h"

#include <lambda_p_script/expression.h>
#include <lambda_p_script/call.h>
#include <core/reference.h>
#include <lambda_p_script/reference.h>
#include <lambda_p_script/constant.h>
#include <core/expression.h>
#include <core/reference.h>
#include <core/routine.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_script_io/synthesizer.h>
#include <lambda_p_script_io/routine.h>
#include <core/cluster.h>
#include <lambda_p_script/parameters.h>
#include <lambda_p_script/remap.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

lambda_p_script_io::expression::expression (boost::shared_ptr <lambda_p_script::cluster::node> cluster_a, std::map <boost::shared_ptr <mu::core::expression>, size_t> & reservations_a, boost::shared_ptr <lambda_p_script::call> call_a, boost::shared_ptr <mu::core::node> node_a)
	: node (node_a),
	reservations (reservations_a),
	call_m (call_a),
	cluster (cluster_a)
{
	(*node_a) (this);
}

void lambda_p_script_io::expression::operator () (mu::core::expression * set_a)
{
	auto value (boost::static_pointer_cast <mu::core::expression> (node));
	auto existing (reservations.find (value));
	assert (existing != reservations.end ());
	call_m->arguments.push_back (boost::make_shared <lambda_p_script::expression> (existing->second));
}

void lambda_p_script_io::expression::operator () (mu::core::parameters * parameters_a)
{
	call_m->arguments.push_back (boost::make_shared <lambda_p_script::parameters> ());
}

void lambda_p_script_io::expression::operator () (mu::core::reference * reference_a)
{
	auto value (boost::static_pointer_cast <mu::core::reference> (node));
	auto existing (reservations.find (value->expression));
	assert (existing != reservations.end ());
	call_m->arguments.push_back (boost::make_shared <lambda_p_script::reference> (existing->second, value->index));
}

void lambda_p_script_io::expression::operator () (mu::core::node * node_a)
{
	auto value (boost::static_pointer_cast <mu::core::node> (node));
	call_m->arguments.push_back (boost::make_shared <lambda_p_script::constant> (value));
}

void lambda_p_script_io::expression::operator () (mu::core::routine * routine_a)
{
	auto value (boost::static_pointer_cast <mu::core::routine> (node));
	call_m->arguments.push_back (boost::make_shared <lambda_p_script::remap> (value));
}