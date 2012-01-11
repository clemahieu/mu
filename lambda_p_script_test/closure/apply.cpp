#include "apply.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p_script/closure/operation.h>
#include <lambda_p_script/closure/apply.h>
#include <lambda_p_script/identity/operation.h>

void lambda_p_script_test::closure::apply::run ()
{
	run_1 ();
}

void lambda_p_script_test::closure::apply::run_1 ()
{
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	auto c1 (boost::shared_ptr <lambda_p::node> (new lambda_p_script::closure::operation (1, boost::shared_ptr <lambda_p_script::operation> (new lambda_p_script::identity::operation))));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto n1 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	arguments.push_back (c1);
	arguments.push_back (n1);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	lambda_p_script::closure::apply apply;
	apply.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto c2 (boost::dynamic_pointer_cast <lambda_p_script::closure::operation> (results [0]));
	assert (c2.get () != nullptr);	
	std::vector <boost::shared_ptr <lambda_p::node>> a2;
	std::vector <boost::shared_ptr <lambda_p::node>> r2;
	(*c2) (errors, a2, r2);
	assert (errors->errors.empty ());
	assert (r2.size () == 1);
	assert (r2 [0] == n1);
}