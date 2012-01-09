#include "synthesizer.h"

#include <lambda_p_script/synthesizer/synthesizer.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_script_test/synthesizer_results.h>

#include <boost/bind.hpp>

void lambda_p_script_test::synthesizer::run ()
{
	run_1 ();
}

void lambda_p_script_test::synthesizer::run_1 ()
{
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_script_test::synthesizer_results results;
	lambda_p_script::synthesizer::synthesizer synthesizer (boost::bind (&lambda_p_script_test::synthesizer_results::operator(), &results, _1), errors);
}