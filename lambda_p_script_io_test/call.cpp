#include "call.h"

#include <lambda_p_script_io/expression.h>
#include <mu/script/call.h>
#include <mu/script/expression.h>
#include <mu/script/reference.h>
#include <mu/core/node.h>
#include <mu/core/expression.h>
#include <mu/core/reference.h>
#include <mu/script/constant.h>
#include <mu/script/cluster/node.h>

#include <boost/make_shared.hpp>

void lambda_p_script_io_test::call::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void lambda_p_script_io_test::call::run_1 ()
{
	std::map <boost::shared_ptr <mu::core::expression>, size_t> reservations;
	boost::shared_ptr <mu::script::call> target (new mu::script::call (1, mu::core::context ()));
	boost::shared_ptr <mu::core::node> node (new mu::core::node);
	auto remapping (boost::make_shared <mu::script::cluster::node> ());
	lambda_p_script_io::expression expression (remapping, reservations, target, node);
	assert (target->arguments.size () == 1);
	auto added (boost::dynamic_pointer_cast <mu::script::constant> (target->arguments [0]));
	assert (added.get () != nullptr);
	assert (added->value == node);
}

void lambda_p_script_io_test::call::run_2 ()
{
	std::map <boost::shared_ptr <mu::core::expression>, size_t> reservations;
	boost::shared_ptr <mu::script::call> target (new mu::script::call (1, mu::core::context ()));
	boost::shared_ptr <mu::core::expression> parameters (new mu::core::expression (mu::core::context ()));
	reservations.insert (std::map <boost::shared_ptr <mu::core::expression>, size_t>::value_type (parameters, 0));
	auto remapping (boost::make_shared <mu::script::cluster::node> ());
	lambda_p_script_io::expression expression (remapping, reservations, target, parameters);
	assert (target->arguments.size () == 1);
	auto added (boost::dynamic_pointer_cast <mu::script::expression> (target->arguments [0]));
	assert (added.get () != nullptr);
	assert (added->index == 0);
}

void lambda_p_script_io_test::call::run_3 ()
{
	std::map <boost::shared_ptr <mu::core::expression>, size_t> reservations;
	boost::shared_ptr <mu::script::call> target (new mu::script::call (1, mu::core::context ()));
	boost::shared_ptr <mu::core::expression> parameters (new mu::core::expression (mu::core::context ()));
	reservations.insert (std::map <boost::shared_ptr <mu::core::expression>, size_t>::value_type (parameters, 0));
	boost::shared_ptr <mu::core::reference> reference (new mu::core::reference (parameters, 0));
	auto remapping (boost::make_shared <mu::script::cluster::node> ());
	lambda_p_script_io::expression expression (remapping, reservations, target, reference);
	assert (target->arguments.size () == 1);
	auto added (boost::dynamic_pointer_cast <mu::script::reference> (target->arguments [0]));
	assert (added.get () != nullptr);
	assert (added->expression == 0);
	assert (added->index == 0);
}