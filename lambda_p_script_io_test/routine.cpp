#include "routine.h"

#include <lambda_p_script_io/routine.h>
#include <lambda_p/expression.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_script/reference.h>
#include <lambda_p_script/expression.h>
#include <lambda_p_script/constant.h>
#include <lambda_p_script/call.h>
#include <lambda_p_script/parameters.h>
#include <lambda_p/parameters.h>
#include <lambda_p/routine.h>
#include <lambda_p_script/cluster/node.h>

#include <boost/make_shared.hpp>

void lambda_p_script_io_test::routine::run ()
{
	run_1 ();
}

void lambda_p_script_io_test::routine::run_1 ()
{
	std::vector <boost::shared_ptr <lambda_p::expression>> calls;
	auto call1 (boost::shared_ptr <lambda_p::expression> (new lambda_p::expression (lambda_p::context ())));
	calls.push_back (call1);
	call1->dependencies.push_back (boost::make_shared <lambda_p::parameters> ());
	auto call2 (boost::shared_ptr <lambda_p::expression> (new lambda_p::expression (lambda_p::context ())));
	call2->dependencies.push_back (call1);
	calls.push_back (call2);
	auto rout (boost::make_shared <lambda_p::routine> (call2));
	auto remapping (boost::make_shared <lambda_p_script::cluster::node> ());
	auto routine (boost::make_shared <lambda_p_script::routine> (boost::make_shared <lambda_p_script::cluster::node> ()));
	lambda_p_script_io::routine r (remapping, rout, routine);
	assert (routine->calls.size () == 2);
	auto c1 (routine->calls [0]);
	assert (c1->results == 0);
	assert (c1->arguments.size () == 1);
	auto a1 (boost::dynamic_pointer_cast <lambda_p_script::parameters> (c1->arguments [0]));
	assert (a1.get () != nullptr);
	auto c2 (routine->calls [1]);
	assert (c2->results == 1);
	assert (c2->arguments.size () == 1);
	auto a2 (boost::dynamic_pointer_cast <lambda_p_script::expression> (c2->arguments [0]));
	assert (a2.get () != nullptr);
	assert (a2->index == 0);
}