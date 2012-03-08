#include "operation.h"

#include <mu/script/closure/operation.h>
#include <mu/script/identity/operation.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/closure/hole.h>

void mu::script_test::closure::operation::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
}

void mu::script_test::closure::operation::run_1 ()
{
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::closure::operation closure (0, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation));
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	closure (mu::script::context (errors, arguments, results));
	assert (errors->errors.empty ());
	assert (results.empty ());
}

void mu::script_test::closure::operation::run_2 ()
{
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::closure::operation closure (1, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation));
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	auto node (boost::shared_ptr <mu::core::node> (new mu::core::node));
	arguments.push_back (node);
	std::vector <boost::shared_ptr <mu::core::node>> results;
	closure (mu::script::context (errors, arguments, results));
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == node);
}

void mu::script_test::closure::operation::run_3 ()
{
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::closure::operation closure (2, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation));
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	arguments.push_back (n1);
	auto n2 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	arguments.push_back (n2);
	std::vector <boost::shared_ptr <mu::core::node>> results;
	closure (mu::script::context (errors, arguments, results));
	assert (errors->errors.empty ());
	assert (results.size () == 2);
	assert (results [0] == n1);
	assert (results [1] == n2);
}

void mu::script_test::closure::operation::run_4 ()
{
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::closure::operation closure (2, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation));
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	arguments.push_back (n1);
	auto n2 (boost::shared_ptr <mu::core::node> (new mu::script::closure::hole));
	arguments.push_back (n2);
	std::vector <boost::shared_ptr <mu::core::node>> results;
	closure (mu::script::context (errors, arguments, results));
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto result (boost::dynamic_pointer_cast <mu::script::closure::operation> (results [0]));
	assert (result.get () != nullptr);
	auto n3 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	std::vector <boost::shared_ptr <mu::core::node>> args2;
	args2.push_back (n3);
	std::vector <boost::shared_ptr <mu::core::node>> res2;
	(*result) (mu::script::context (errors, args2, res2));
	assert (res2.size () == 2);
	assert (res2 [0] == n1);
	assert (res2 [1] == n3);
}

void mu::script_test::closure::operation::run_5 ()
{
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::closure::operation closure (2, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation));
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::script::closure::hole));
	arguments.push_back (n1);
	auto n2 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	arguments.push_back (n2);
	std::vector <boost::shared_ptr <mu::core::node>> results;
	closure (mu::script::context (errors, arguments, results));
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto result (boost::dynamic_pointer_cast <mu::script::closure::operation> (results [0]));
	assert (result.get () != nullptr);
	auto n3 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	std::vector <boost::shared_ptr <mu::core::node>> args2;
	args2.push_back (n3);
	std::vector <boost::shared_ptr <mu::core::node>> res2;
	(*result) (mu::script::context (errors, args2, res2));
	assert (res2.size () == 2);
	assert (res2 [0] == n3);
	assert (res2 [1] == n2);
}