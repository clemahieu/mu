#include <mu/script_test/package.get_recursive.h>

#include <mu/script/package.get_recursive.h>
#include <mu/script/package.node.h>
#include <mu/script/string.node.h>
#include <mu/core/errors.error_list.h>

void mu::script_test::package::get_recursive::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void mu::script_test::package::get_recursive::run_1 ()
{
	auto package (boost::shared_ptr <mu::script::package::node> (new mu::script::package::node));
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::package::get_recursive recursive;
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	arguments.push_back (package);
	std::vector <boost::shared_ptr <mu::core::node>> results;
	recursive.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == package);
}

void mu::script_test::package::get_recursive::run_2 ()
{
	auto package (boost::shared_ptr <mu::script::package::node> (new mu::script::package::node));
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	package->items [std::wstring (L"a")] = n1;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::package::get_recursive recursive;
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	arguments.push_back (package);
	arguments.push_back (boost::shared_ptr <mu::core::node> (new mu::script::string::node (std::wstring (L"a"))));
	std::vector <boost::shared_ptr <mu::core::node>> results;
	recursive.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == n1);
}

void mu::script_test::package::get_recursive::run_3 ()
{
	auto package (boost::shared_ptr <mu::script::package::node> (new mu::script::package::node));
	auto package1 (boost::shared_ptr <mu::script::package::node> (new mu::script::package::node));
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	package->items [std::wstring (L"a")] = package1;
	package1->items [std::wstring (L"b")] = n1;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::package::get_recursive recursive;
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	arguments.push_back (package);
	arguments.push_back (boost::shared_ptr <mu::core::node> (new mu::script::string::node (std::wstring (L"a"))));
	arguments.push_back (boost::shared_ptr <mu::core::node> (new mu::script::string::node (std::wstring (L"b"))));
	std::vector <boost::shared_ptr <mu::core::node>> results;
	recursive.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == n1);
}
