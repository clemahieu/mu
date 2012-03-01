#include "expression.h"

#include <mu/script/runtime/expression.h>
#include <mu/script/runtime/call.h>
#include <mu/core/reference.h>
#include <mu/script/runtime/reference.h>
#include <mu/script/runtime/constant.h>
#include <mu/core/expression.h>
#include <mu/core/reference.h>
#include <mu/core/routine.h>
#include <mu/script/runtime/routine.h>
#include <mu/script_io/synthesizer.h>
#include <mu/script_io/routine.h>
#include <mu/core/cluster.h>
#include <mu/script/runtime/parameters.h>
#include <mu/script/runtime/routine.h>
#include <mu/script_io/cluster.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

mu::script_io::expression::expression (mu::script_io::cluster & cluster_a, std::map <boost::shared_ptr <mu::core::expression>, size_t> & reservations_a, boost::shared_ptr <mu::script::runtime::call> call_a, boost::shared_ptr <mu::core::node> node_a)
	: node (node_a),
	reservations (reservations_a),
	call_m (call_a),
	cluster (cluster_a)
{
	(*node_a) (this);
}

void mu::script_io::expression::operator () (mu::core::expression * set_a)
{
	auto value (boost::static_pointer_cast <mu::core::expression> (node));
	auto existing (reservations.find (value));
	assert (existing != reservations.end ());
	call_m->arguments.push_back (boost::make_shared <mu::script::runtime::expression> (existing->second));
}

void mu::script_io::expression::operator () (mu::core::parameters * parameters_a)
{
	call_m->arguments.push_back (boost::make_shared <mu::script::runtime::parameters> ());
}

void mu::script_io::expression::operator () (mu::core::reference * reference_a)
{
	auto value (boost::static_pointer_cast <mu::core::reference> (node));
	auto existing (reservations.find (value->expression));
	assert (existing != reservations.end ());
	call_m->arguments.push_back (boost::make_shared <mu::script::runtime::reference> (existing->second, value->index));
}

void mu::script_io::expression::operator () (mu::core::node * node_a)
{
	auto value (boost::static_pointer_cast <mu::core::node> (node));
	call_m->arguments.push_back (boost::make_shared <mu::script::runtime::constant> (value));
}

void mu::script_io::expression::operator () (mu::core::routine * routine_a)
{
	auto value (boost::static_pointer_cast <mu::core::routine> (node));
	auto routine (cluster.process_routine (value));
	call_m->arguments.push_back (boost::make_shared <mu::script::runtime::constant> (routine));
}