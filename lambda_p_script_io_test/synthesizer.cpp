#include "synthesizer.h"

#include <lambda_p_script_io/synthesizer.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_script_io_test/synthesizer_results.h>
#include <lambda_p/routine.h>
#include <lambda_p/call.h>
#include <lambda_p/reference.h>
#include <lambda_p/set.h>
#include <lambda_p_script/routine.h>

#include <boost/bind.hpp>

void lambda_p_script_io_test::synthesizer::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_script_io_test::synthesizer::run_1 ()
{
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_script_test::synthesizer_results results;
	lambda_p_script_io::synthesizer synthesizer (boost::bind (&lambda_p_script_test::synthesizer_results::operator(), &results, _1));
	auto routine (boost::shared_ptr <lambda_p::routine> (new lambda_p::routine));
	routine->body = boost::shared_ptr <lambda_p::set> (new lambda_p::set);
	synthesizer (routine);
	assert (errors->errors.empty ());
	assert (results.routines.size () == 1);
	auto result (results.routines [0]);
	assert (result->calls.size () == 1);
}

void lambda_p_script_io_test::synthesizer::run_2 ()
{
	// [[:~]]
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_script_test::synthesizer_results results;
	lambda_p_script_io::synthesizer synthesizer (boost::bind (&lambda_p_script_test::synthesizer_results::operator(), &results, _1));
	auto routine (boost::shared_ptr <lambda_p::routine> (new lambda_p::routine));
	auto root (boost::shared_ptr <lambda_p::set> (new lambda_p::set));
	routine->body = root;
	auto parameters (boost::shared_ptr <lambda_p::call> (new lambda_p::call));
	root->dependencies.push_back (parameters);
	parameters->dependencies.push_back (routine->parameters);
	synthesizer (routine);
	assert (errors->errors.empty ());
	assert (results.routines.size () == 1);
	auto result (results.routines [0]);
	assert (result->calls.size () == 2);
}