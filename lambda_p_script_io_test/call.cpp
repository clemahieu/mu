#include "call.h"

#include <lambda_p_script_io/expression.h>
#include <lambda_p_script/call.h>
#include <lambda_p_script/expression.h>
#include <lambda_p_script/reference.h>
#include <lambda_p/node.h>
#include <lambda_p/expression.h>
#include <lambda_p/reference.h>
#include <lambda_p_script/constant.h>

void lambda_p_script_io_test::call::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void lambda_p_script_io_test::call::run_1 ()
{
	std::map <boost::shared_ptr <lambda_p::expression>, size_t> reservations;
	boost::shared_ptr <lambda_p_script::call> target (new lambda_p_script::call (1));
	boost::shared_ptr <lambda_p::node> node (new lambda_p::node);
	lambda_p_script_io::expression expression (reservations, target, node);
	assert (target->arguments.size () == 1);
	auto added (boost::dynamic_pointer_cast <lambda_p_script::constant> (target->arguments [0]));
	assert (added.get () != nullptr);
	assert (added->value == node);
}

void lambda_p_script_io_test::call::run_2 ()
{
	std::map <boost::shared_ptr <lambda_p::expression>, size_t> reservations;
	boost::shared_ptr <lambda_p_script::call> target (new lambda_p_script::call (1));
	boost::shared_ptr <lambda_p::expression> parameters (new lambda_p::expression (lambda_p::context ()));
	reservations.insert (std::map <boost::shared_ptr <lambda_p::expression>, size_t>::value_type (parameters, 0));
	lambda_p_script_io::expression expression (reservations, target, parameters);
	assert (target->arguments.size () == 1);
	auto added (boost::dynamic_pointer_cast <lambda_p_script::expression> (target->arguments [0]));
	assert (added.get () != nullptr);
	assert (added->index == 0);
}

void lambda_p_script_io_test::call::run_3 ()
{
	std::map <boost::shared_ptr <lambda_p::expression>, size_t> reservations;
	boost::shared_ptr <lambda_p_script::call> target (new lambda_p_script::call (1));
	boost::shared_ptr <lambda_p::expression> parameters (new lambda_p::expression (lambda_p::context ()));
	reservations.insert (std::map <boost::shared_ptr <lambda_p::expression>, size_t>::value_type (parameters, 0));
	boost::shared_ptr <lambda_p::reference> reference (new lambda_p::reference (parameters, 0));
	lambda_p_script_io::expression expression (reservations, target, reference);
	assert (target->arguments.size () == 1);
	auto added (boost::dynamic_pointer_cast <lambda_p_script::reference> (target->arguments [0]));
	assert (added.get () != nullptr);
	assert (added->expression == 0);
	assert (added->index == 0);
}