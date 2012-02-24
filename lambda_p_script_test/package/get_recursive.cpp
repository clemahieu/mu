#include "get_recursive.h"

#include <lambda_p_script/package/get_recursive.h>
#include <lambda_p_script/package/node.h>
#include <lambda_p_script/string/node.h>
#include <core/errors/error_list.h>

void lambda_p_script_test::package::get_recursive::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void lambda_p_script_test::package::get_recursive::run_1 ()
{
	auto package (boost::shared_ptr <lambda_p_script::package::node> (new lambda_p_script::package::node));
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	lambda_p_script::package::get_recursive recursive;
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	arguments.push_back (package);
	std::vector <boost::shared_ptr <mu::core::node>> results;
	recursive.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == package);
}

void lambda_p_script_test::package::get_recursive::run_2 ()
{
	auto package (boost::shared_ptr <lambda_p_script::package::node> (new lambda_p_script::package::node));
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	package->items [std::wstring (L"a")] = n1;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	lambda_p_script::package::get_recursive recursive;
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	arguments.push_back (package);
	arguments.push_back (boost::shared_ptr <mu::core::node> (new lambda_p_script::string::node (std::wstring (L"a"))));
	std::vector <boost::shared_ptr <mu::core::node>> results;
	recursive.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == n1);
}

void lambda_p_script_test::package::get_recursive::run_3 ()
{
	auto package (boost::shared_ptr <lambda_p_script::package::node> (new lambda_p_script::package::node));
	auto package1 (boost::shared_ptr <lambda_p_script::package::node> (new lambda_p_script::package::node));
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	package->items [std::wstring (L"a")] = package1;
	package1->items [std::wstring (L"b")] = n1;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	lambda_p_script::package::get_recursive recursive;
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	arguments.push_back (package);
	arguments.push_back (boost::shared_ptr <mu::core::node> (new lambda_p_script::string::node (std::wstring (L"a"))));
	arguments.push_back (boost::shared_ptr <mu::core::node> (new lambda_p_script::string::node (std::wstring (L"b"))));
	std::vector <boost::shared_ptr <mu::core::node>> results;
	recursive.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == n1);
}