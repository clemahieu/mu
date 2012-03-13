#include "get.h"

#include <mu/core/errors/error_list.h>
#include <mu/script/package/get.h>
#include <mu/script/package/node.h>
#include <mu/script/string/node.h>
#include <mu/script/context.h>

void mu::script_test::package::get::run ()
{
	run_1 ();
}

void mu::script_test::package::get::run_1 ()
{
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	auto data (boost::shared_ptr <mu::script::package::node> (new mu::script::package::node));
	auto name (boost::shared_ptr <mu::script::string::node> (new mu::script::string::node (std::wstring (L"test"))));
	mu::script::package::get get;
	auto node (boost::shared_ptr <mu::core::node> (new mu::core::node));
	data->items [std::wstring (L"test")] = node;
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	arguments.push_back (data);
	arguments.push_back (name);
	std::vector <boost::shared_ptr <mu::core::node>> results;
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	get (ctx);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == node);
}