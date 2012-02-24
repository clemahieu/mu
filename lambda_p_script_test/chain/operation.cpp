#include "operation.h"

#include <core/errors/error_list.h>
#include <lambda_p_script/chain/operation.h>
#include <lambda_p_script_test/chain/ten_count.h>
#include <lambda_p_script/integer/node.h>

void lambda_p_script_test::chain::operation::run ()
{
	run_1 ();
}

void lambda_p_script_test::chain::operation::run_1 ()
{
	auto operation (boost::shared_ptr <mu::core::node> (new lambda_p_script_test::chain::ten_count));
	auto count (boost::shared_ptr <lambda_p_script::integer::node> (new lambda_p_script::integer::node (50)));
	lambda_p_script::chain::operation chain;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	arguments.push_back (operation);
	arguments.push_back (count);
	chain.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto result (boost::dynamic_pointer_cast <lambda_p_script::integer::node> (results [0]));
	assert (result->value == 40);
}