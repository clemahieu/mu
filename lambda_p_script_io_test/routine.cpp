#include "routine.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p/routine.h>
#include <lambda_p/call.h>
#include <lambda_p_script_io/routine.h>
#include <lambda_p/parameters.h>

#include <boost/shared_ptr.hpp>

void lambda_p_script_io_test::routine::run ()
{
	run_1 ();
}

void lambda_p_script_io_test::routine::run_1 ()
{
	auto routine (boost::shared_ptr <lambda_p::routine> (new lambda_p::routine));
	auto root (boost::shared_ptr <lambda_p::call> (new lambda_p::call));
	routine->call = root;
	auto parameters (boost::shared_ptr <lambda_p::call> (new lambda_p::call));
	root->dependencies.push_back (parameters);
	parameters->dependencies.push_back (routine->parameters);
	lambda_p_script_io::routine r (routine);
	auto i (r.expressions.begin ());
	assert (*i == parameters);
	++i;
	assert (*i == root);
}