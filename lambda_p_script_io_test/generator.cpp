#include "generator.h"

#include <lambda_p_script_io/generator.h>
#include <lambda_p/call.h>
#include <lambda_p/set.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_script/reference.h>
#include <lambda_p_script/expression.h>
#include <lambda_p_script/constant.h>
#include <lambda_p_script/call.h>

void lambda_p_script_io_test::generator::run ()
{
	run_1 ();
}

void lambda_p_script_io_test::generator::run_1 ()
{
	std::vector <boost::shared_ptr <lambda_p::expression>> calls;
	auto parameters (boost::shared_ptr <lambda_p::set> (new lambda_p::set));
	auto call1 (boost::shared_ptr <lambda_p::call> (new lambda_p::call));
	calls.push_back (call1);
	call1->dependencies.push_back (parameters);
	auto call2 (boost::shared_ptr <lambda_p::call> (new lambda_p::call));
	call2->dependencies.push_back (call1);
	calls.push_back (call2);
	lambda_p_script_io::generator generator (calls, parameters);
	auto routine (generator.result);
	assert (routine->calls.size () == 2);
	auto c1 (routine->calls [0]);
	assert (c1->results == 1);
	assert (c1->arguments.size () == 1);
	auto a1 (boost::dynamic_pointer_cast <lambda_p_script::expression> (c1->arguments [0]));
	assert (a1.get () != nullptr);
	assert (a1->index == 0);
	auto c2 (routine->calls [1]);
	assert (c2->results == 2);
	assert (c2->arguments.size () == 1);
	auto a2 (boost::dynamic_pointer_cast <lambda_p_script::expression> (c2->arguments [0]));
	assert (a2.get () != nullptr);
	assert (a2->index == 1);
}