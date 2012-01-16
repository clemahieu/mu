#include "get.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p_script/package/get.h>
#include <lambda_p_script/package/node.h>
#include <lambda_p_script/string/node.h>

void lambda_p_script_test::package::get::run ()
{
	run_1 ();
}

void lambda_p_script_test::package::get::run_1 ()
{
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	auto data (boost::shared_ptr <lambda_p_script::package::node> (new lambda_p_script::package::node));
	auto name (boost::shared_ptr <lambda_p_script::string::node> (new lambda_p_script::string::node (std::wstring (L"test"))));
	lambda_p_script::package::get get;
	auto node (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	data->items [std::wstring (L"test")] = node;
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	arguments.push_back (data);
	arguments.push_back (name);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	get (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == node);
}