#include "node_list_test.h"

#include <lambda_p/binder/list.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_kernel/nodes/data.h>

void lambda_p_test::node_list_test::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
}

void lambda_p_test::node_list_test::run_1 ()
{
	lambda_p::binder::list one;
	lambda_p::binder::list two;
	lambda_p::errors::error_list problems;
	one.merge (two, problems);
	assert (problems.errors.empty ());
}

void lambda_p_test::node_list_test::run_2 ()
{
	lambda_p::binder::list one;
	lambda_p::binder::list two;
	lambda_p::errors::error_list problems;
	one [0] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::nodes::data (std::wstring ()));
	one.merge (two, problems);
	assert (problems.errors.empty ());
	assert (one.nodes.size () == 1);
	assert (two.nodes.empty ());
	assert (one [0].get () != nullptr);
}

void lambda_p_test::node_list_test::run_3 ()
{
	lambda_p::binder::list one;
	lambda_p::binder::list two;
	lambda_p::errors::error_list problems;
	two [0] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::nodes::data (std::wstring ()));
	one.merge (two, problems);
	assert (problems.errors.empty ());
	assert (one.nodes.size () == 1);
	assert (two.nodes.size () == 1);
	assert (one [0].get () != nullptr);
}

void lambda_p_test::node_list_test::run_4 ()
{
	lambda_p::binder::list one;
	lambda_p::binder::list two;
	lambda_p::errors::error_list problems;
	two [1] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::nodes::data (std::wstring ()));
	one.merge (two, problems);
	assert (problems.errors.empty ());
	assert (one.nodes.size () == 2);
	assert (two.nodes.size () == 2);
	assert (one [0].get () == nullptr);
	assert (one [1].get () != nullptr);
}

void lambda_p_test::node_list_test::run_5 ()
{
	lambda_p::binder::list one;
	lambda_p::binder::list two;
	lambda_p::errors::error_list problems;
	one [1] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::nodes::data (std::wstring ()));
	two [1] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::nodes::data (std::wstring ()));
	one.merge (two, problems);
	assert (!problems.errors.empty ());
}

void lambda_p_test::node_list_test::run_6 ()
{
	lambda_p::binder::list one;
	lambda_p::binder::list two;
	lambda_p::errors::error_list problems;
	one [0] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::nodes::data (std::wstring ()));
	two [1] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::nodes::data (std::wstring ()));
	one.merge (two, problems);
	assert (problems.errors.empty ());
	assert (one.nodes.size () == 2);
	assert (two.nodes.size () == 2);
	assert (one [0].get () != nullptr);
	assert (one [1].get () != nullptr);
	assert (two [0].get () == nullptr);
	assert (two [1].get () != nullptr);
}