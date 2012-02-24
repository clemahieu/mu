#include "create.h"

#include <lambda_p_script/package/create.h>
#include <lambda_p_script/package/node.h>
#include <mu/core/errors/error_list.h>

void lambda_p_script_test::package::create::run ()
{
	run_1 ();
}

void lambda_p_script_test::package::create::run_1 ()
{
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	lambda_p_script::package::create create;
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	create (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto node (boost::dynamic_pointer_cast <lambda_p_script::package::node> (results [0]));
	assert (node.get () != nullptr);
}