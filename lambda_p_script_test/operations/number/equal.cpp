#include "equal.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p_script/integer/equal.h>
#include <lambda_p_script/integer/node.h>
#include <lambda_p_script/bool_c/node.h>

void lambda_p_script_test::operations::number::equal::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void lambda_p_script_test::operations::number::equal::run_1 ()
{
	lambda_p_script::integer::equal equal;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	arguments.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::node (3)));
	arguments.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::node (5)));
	equal (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto result (boost::dynamic_pointer_cast <lambda_p_script::bool_c::node> (results [0]));
	assert (result.get () != nullptr);
	assert (result->value == false);
}

void lambda_p_script_test::operations::number::equal::run_2 ()
{
	lambda_p_script::integer::equal equal;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	arguments.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::node (3)));
	arguments.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::node (3)));
	equal (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto result (boost::dynamic_pointer_cast <lambda_p_script::bool_c::node> (results [0]));
	assert (result.get () != nullptr);
	assert (result->value == true);
}

void lambda_p_script_test::operations::number::equal::run_3 ()
{
	lambda_p_script::integer::equal equal;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	arguments.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::node (3)));
	arguments.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	equal (errors, arguments, results);
	assert (!errors->errors.empty ());
}