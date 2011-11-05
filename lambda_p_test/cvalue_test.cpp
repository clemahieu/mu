#include "cvalue_test.h"

#include <lambda_p_kernel/cvalue.h>
#include <lambda_p/binder/data.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p/builder.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p_kernel/bool_c.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p_kernel/bool_binder.h>

void lambda_p_test::cvalue_test::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_test::cvalue_test::run_1 ()
{
	lambda_p::builder condition_builder;
	condition_builder (L"result; bool; bool `false; result; :;");
	boost::shared_ptr <lambda_p::binder::node_list> condition_list (new lambda_p::binder::node_list);
	condition_list->operator[] (0) = boost::shared_ptr <lambda_p_kernel::bool_binder> (new lambda_p_kernel::bool_binder);
	boost::shared_ptr <lambda_p_kernel::routine> condition (new lambda_p_kernel::routine (condition_builder.routines.routines->operator[] (0)));
	lambda_p::builder builder;
	builder (L"result; cvalue condition arguments a b; cvalue condition arguments a b; result; :;");
	lambda_p::binder::node_list list;
	list [0] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::cvalue);
	list [1] = boost::shared_ptr <lambda_p::binder::node> (condition);
	list [2] = condition_list;
	list [3] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p::binder::data (std::wstring (L"a")));
	list [4] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p::binder::data (std::wstring (L"b")));
	lambda_p::binder::node_list result;
	lambda_p_kernel::apply apply;
	lambda_p::errors::error_list problems;
	lambda_p_kernel::routine routine (builder.routines.routines->operator[] (0));
	apply.core (routine, list, problems, result);
	assert (problems.errors.empty ());
	assert (result.nodes.size () == 1);
	assert ((boost::dynamic_pointer_cast <lambda_p::binder::data> (result [0]))->string ().compare (std::wstring (L"b")) == 0);
}

void lambda_p_test::cvalue_test::run_2 ()
{
	lambda_p::builder condition_builder;
	condition_builder (L"result; bool; bool `true; result; :;");
	boost::shared_ptr <lambda_p::binder::node_list> condition_list (new lambda_p::binder::node_list);
	condition_list->operator[] (0) = boost::shared_ptr <lambda_p_kernel::bool_binder> (new lambda_p_kernel::bool_binder);
	boost::shared_ptr <lambda_p_kernel::routine> condition (new lambda_p_kernel::routine (condition_builder.routines.routines->operator[] (0)));
	lambda_p::builder builder;
	builder (L"result; cvalue condition arguments a b; cvalue condition arguments a b; result; :;");
	lambda_p::binder::node_list list;
	list [0] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::cvalue);
	list [1] = boost::shared_ptr <lambda_p::binder::node> (condition);
	list [2] = condition_list;
	list [3] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p::binder::data (std::wstring (L"a")));
	list [4] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p::binder::data (std::wstring (L"b")));
	lambda_p::binder::node_list result;
	lambda_p_kernel::apply apply;
	lambda_p::errors::error_list problems;
	lambda_p_kernel::routine routine (builder.routines.routines->operator[] (0));
	apply.core (routine, list, problems, result);
	assert (problems.errors.empty ());
	assert (result.nodes.size () == 1);
	assert ((boost::dynamic_pointer_cast <lambda_p::binder::data> (result [0]))->string ().compare (std::wstring (L"a")) == 0);
}