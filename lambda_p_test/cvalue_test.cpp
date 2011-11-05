#include "cvalue_test.h"

#include <lambda_p_kernel/cvalue.h>
#include <lambda_p/binder/data.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p/builder.h>
#include <lambda_p/binder/list.h>
#include <lambda_p_kernel/bool_c.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_kernel/routine.h>

void lambda_p_test::cvalue_test::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_test::cvalue_test::run_1 ()
{
	lambda_p::builder builder;
	builder (L"result; cvalue boolean a b; cvalue boolean a b; result; :;");
	lambda_p::binder::list list;
	list [0] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::cvalue);
	list [1] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::bool_c (false));
	list [2] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p::binder::data (std::wstring (L"a")));
	list [3] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p::binder::data (std::wstring (L"b")));
	lambda_p::binder::list result;
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
	lambda_p::builder builder;
	builder (L"result; cvalue boolean a b; cvalue boolean a b; result; :;");
	lambda_p::binder::list list;
	list [0] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::cvalue);
	list [1] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::bool_c (true));
	list [2] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p::binder::data (std::wstring (L"a")));
	list [3] = boost::shared_ptr <lambda_p::binder::node> (new lambda_p::binder::data (std::wstring (L"b")));
	lambda_p::binder::list result;
	lambda_p_kernel::apply apply;
	lambda_p::errors::error_list problems;
	lambda_p_kernel::routine routine (builder.routines.routines->operator[] (0));
	apply.core (routine, list, problems, result);
	assert (problems.errors.empty ());
	assert (result.nodes.size () == 1);
	assert ((boost::dynamic_pointer_cast <lambda_p::binder::data> (result [0]))->string ().compare (std::wstring (L"a")) == 0);
}