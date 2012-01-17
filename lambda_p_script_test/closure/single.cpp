#include "single.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p_script/closure/single.h>
#include <lambda_p_script/identity/operation.h>

void lambda_p_script_test::closure::single::run ()
{
	run_1 ();
}

void lambda_p_script_test::closure::single::run_1 ()
{
	std::vector <boost::shared_ptr <lambda_p::node>> closed;
	auto n1 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	closed.push_back (n1);
	lambda_p_script::closure::single single (closed, boost::shared_ptr <lambda_p_script::operation> (new lambda_p_script::identity::operation));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto n2 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	arguments.push_back (n2);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	single.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 2);
	assert (results [0] == n1);
	assert (results [1] == n2);
}