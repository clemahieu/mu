#include "equal.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p_script/operations/number/equal.h>
#include <lambda_p_script/nodes/number.h>
#include <lambda_p_script/nodes/bool_c.h>

void lambda_p_script_test::operations::number::equal::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void lambda_p_script_test::operations::number::equal::run_1 ()
{
	lambda_p_script::operations::number::equal equal;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	arguments.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::nodes::number (3)));
	arguments.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::nodes::number (5)));
	equal (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto result (boost::dynamic_pointer_cast <lambda_p_script::nodes::bool_c> (results [0]));
	assert (result.get () != nullptr);
	assert (result->value == false);
}

void lambda_p_script_test::operations::number::equal::run_2 ()
{
	lambda_p_script::operations::number::equal equal;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	arguments.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::nodes::number (3)));
	arguments.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::nodes::number (3)));
	equal (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto result (boost::dynamic_pointer_cast <lambda_p_script::nodes::bool_c> (results [0]));
	assert (result.get () != nullptr);
	assert (result->value == true);
}

void lambda_p_script_test::operations::number::equal::run_3 ()
{
	lambda_p_script::operations::number::equal equal;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	arguments.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::nodes::number (3)));
	arguments.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	equal (errors, arguments, results);
	assert (!errors->errors.empty ());
}

void lambda_p_script_test::operations::number::equal::run_4 ()
{
	lambda_p_script::operations::number::equal equal;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	arguments.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::nodes::number (3)));
	arguments.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::nodes::number (3)));
	arguments.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::nodes::number (3)));
	equal (errors, arguments, results);
	assert (!errors->errors.empty ());
}