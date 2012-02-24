#include "single.h"

#include <mu/core/errors/error_list.h>
#include <mu/script/closure/single.h>
#include <mu/script/identity/operation.h>

void lambda_p_script_test::closure::single::run ()
{
	run_1 ();
}

void lambda_p_script_test::closure::single::run_1 ()
{
	std::vector <boost::shared_ptr <mu::core::node>> closed;
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	closed.push_back (n1);
	mu::script::closure::single single (closed, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation));
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	auto n2 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	arguments.push_back (n2);
	std::vector <boost::shared_ptr <mu::core::node>> results;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	single.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 2);
	assert (results [0] == n1);
	assert (results [1] == n2);
}