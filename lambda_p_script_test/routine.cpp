#include "routine.h"

#include <lambda_p_script/routine.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_script/call.h>

void lambda_p_script_test::routine::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_script_test::routine::run_1 ()
{
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	lambda_p_script::routine routine;
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine (errors, arguments, results);
	assert (errors->errors.empty ());
}

void lambda_p_script_test::routine::run_2 ()
{
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	lambda_p_script::routine routine;
	routine.calls.push_back (boost::shared_ptr <lambda_p_script::call> (new lambda_p_script::call (0)));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine (errors, arguments, results);
	assert (!errors->errors.empty ());
}