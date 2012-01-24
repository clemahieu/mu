#include "routine.h"

#include <lambda_p_script/routine.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_script/call.h>
#include <lambda_p_script/identity/operation.h>
#include <lambda_p_script/constant.h>
#include <lambda_p_script/expression.h>

void lambda_p_script_test::routine::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void lambda_p_script_test::routine::run_1 ()
{
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	lambda_p_script::routine routine;
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine.perform (errors, arguments, results);
	assert (errors->errors.empty ());
}

void lambda_p_script_test::routine::run_2 ()
{
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	lambda_p_script::routine routine;
	routine.calls.push_back (boost::shared_ptr <lambda_p_script::call> (new lambda_p_script::call (0, lambda_p::context ())));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine.perform (errors, arguments, results);
	assert (!errors->errors.empty ());
}

void lambda_p_script_test::routine::run_3 ()
{
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	lambda_p_script::routine routine;
	auto call (boost::shared_ptr <lambda_p_script::call> (new lambda_p_script::call (1, lambda_p::context ())));
	call->arguments.push_back (boost::shared_ptr <lambda_p_script::constant> (new lambda_p_script::constant (boost::shared_ptr <lambda_p::node> (new lambda_p_script::identity::operation))));
	routine.calls.push_back (call);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine.perform (errors, arguments, results);
	assert (errors->errors.empty ());
}

void lambda_p_script_test::routine::run_4 ()
{
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	lambda_p_script::routine routine;
	auto call (boost::shared_ptr <lambda_p_script::call> (new lambda_p_script::call (1, lambda_p::context ())));
	call->arguments.push_back (boost::shared_ptr <lambda_p_script::expression> (new lambda_p_script::expression (0)));
	routine.calls.push_back (call);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto node (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	arguments.push_back (node);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == node);
}