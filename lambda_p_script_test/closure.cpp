#include "closure.h"

#include <lambda_p_script/closure/operation.h>
#include <lambda_p_script/identity/operation.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_script/closure/hole.h>

void lambda_p_script_test::closure::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
}

void lambda_p_script_test::closure::run_1 ()
{
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_script::closure::operation closure (0, boost::shared_ptr <lambda_p_script::operation> (new lambda_p_script::identity::operation));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	closure (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.empty ());
}

void lambda_p_script_test::closure::run_2 ()
{
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_script::closure::operation closure (1, boost::shared_ptr <lambda_p_script::operation> (new lambda_p_script::identity::operation));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto node (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	arguments.push_back (node);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	closure (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == node);
}

void lambda_p_script_test::closure::run_3 ()
{
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_script::closure::operation closure (2, boost::shared_ptr <lambda_p_script::operation> (new lambda_p_script::identity::operation));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto n1 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	arguments.push_back (n1);
	auto n2 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	arguments.push_back (n2);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	closure (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 2);
	assert (results [0] == n1);
	assert (results [1] == n2);
}

void lambda_p_script_test::closure::run_4 ()
{
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_script::closure::operation closure (2, boost::shared_ptr <lambda_p_script::operation> (new lambda_p_script::identity::operation));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto n1 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	arguments.push_back (n1);
	auto n2 (boost::shared_ptr <lambda_p::node> (new lambda_p_script::closure::hole));
	arguments.push_back (n2);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	closure (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto result (boost::dynamic_pointer_cast <lambda_p_script::closure::operation> (results [0]));
	assert (result.get () != nullptr);
	auto n3 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	std::vector <boost::shared_ptr <lambda_p::node>> args2;
	args2.push_back (n3);
	std::vector <boost::shared_ptr <lambda_p::node>> res2;
	(*result) (errors, args2, res2);
	assert (res2.size () == 2);
	assert (res2 [0] == n1);
	assert (res2 [1] == n3);
}

void lambda_p_script_test::closure::run_5 ()
{
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_script::closure::operation closure (2, boost::shared_ptr <lambda_p_script::operation> (new lambda_p_script::identity::operation));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto n1 (boost::shared_ptr <lambda_p::node> (new lambda_p_script::closure::hole));
	arguments.push_back (n1);
	auto n2 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	arguments.push_back (n2);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	closure (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto result (boost::dynamic_pointer_cast <lambda_p_script::closure::operation> (results [0]));
	assert (result.get () != nullptr);
	auto n3 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	std::vector <boost::shared_ptr <lambda_p::node>> args2;
	args2.push_back (n3);
	std::vector <boost::shared_ptr <lambda_p::node>> res2;
	(*result) (errors, args2, res2);
	assert (res2.size () == 2);
	assert (res2 [0] == n3);
	assert (res2 [1] == n2);
}