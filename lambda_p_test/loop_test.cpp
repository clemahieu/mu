#include "loop_test.h"

#include <lambda_p/builder.h>
#include <lambda_p/binder/list.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p_kernel/subtract.h>
#include <lambda_p_kernel/number.h>
#include <lambda_p_kernel/equals.h>
#include <lambda_p_kernel/loop.h>
#include <lambda_p/binder/list_binder.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_kernel/bool_c.h>
#include <lambda_p_kernel/not.h>

void lambda_p_test::loop_test::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void lambda_p_test::loop_test::run_1 ()
{
	lambda_p::builder inner_builder;
	inner_builder (L"subtract equals not new_value one zero next; subtract equals not value one zero; subtract value one; new_value; equals new_value zero; diff; not diff; next; :;");
	lambda_p::builder outer_builder;
	outer_builder (L"result; loop list routine subtract equals not value one zero; list subtract equals not value one zero; args; loop routine args; results; results ; 1 2 3 result 5 6; :;");
	lambda_p::binder::list list;
	list [0] = boost::shared_ptr <lambda_p_kernel::loop> (new lambda_p_kernel::loop);
	list [1] = boost::shared_ptr <lambda_p::binder::list_binder> (new lambda_p::binder::list_binder);
	boost::shared_ptr <lambda_p_kernel::routine> routine (new lambda_p_kernel::routine (inner_builder.routines.routines->operator[] (0)));
	list [2] = routine;
	list [3] = boost::shared_ptr <lambda_p_kernel::subtract> (new lambda_p_kernel::subtract);
	list [4] = boost::shared_ptr <lambda_p_kernel::equals> (new lambda_p_kernel::equals);
	list [5] = boost::shared_ptr <lambda_p_kernel::not> (new lambda_p_kernel::not);
	list [6] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (1));
	list [7] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (1));
	list [8] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (0));
	lambda_p_kernel::apply apply;
	boost::shared_ptr <lambda_p_kernel::routine> loop (new lambda_p_kernel::routine (outer_builder.routines.routines->operator[] (0)));
	lambda_p::errors::error_list problems;
	lambda_p::binder::list results;
	apply.core (*loop, list, problems, results);
	assert (problems.errors.empty ());
	assert (results.nodes.size () == 1);
	boost::shared_ptr <lambda_p_kernel::number> number (boost::dynamic_pointer_cast <lambda_p_kernel::number> (results [0]));
	assert (number.get () != nullptr);
	assert (number->value == 0);
}

void lambda_p_test::loop_test::run_2 ()
{
	lambda_p::builder inner_builder;
	inner_builder (L"subtract equals not new_value one zero next; subtract equals not value one zero; subtract value one; new_value; equals new_value zero; diff; not diff; next; :;");
	lambda_p::builder outer_builder;
	outer_builder (L"result; loop list routine subtract equals not value one zero; list subtract equals not value one zero; args; loop routine args; results; results ; 1 2 3 result 5 6; :;");
	lambda_p::binder::list list;
	list [0] = boost::shared_ptr <lambda_p_kernel::loop> (new lambda_p_kernel::loop);
	list [1] = boost::shared_ptr <lambda_p::binder::list_binder> (new lambda_p::binder::list_binder);
	boost::shared_ptr <lambda_p_kernel::routine> routine (new lambda_p_kernel::routine (inner_builder.routines.routines->operator[] (0)));
	list [2] = routine;
	list [3] = boost::shared_ptr <lambda_p_kernel::subtract> (new lambda_p_kernel::subtract);
	list [4] = boost::shared_ptr <lambda_p_kernel::equals> (new lambda_p_kernel::equals);
	list [5] = boost::shared_ptr <lambda_p_kernel::not> (new lambda_p_kernel::not);
	list [6] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (2));
	list [7] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (1));
	list [8] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (0));
	lambda_p_kernel::apply apply;
	boost::shared_ptr <lambda_p_kernel::routine> loop (new lambda_p_kernel::routine (outer_builder.routines.routines->operator[] (0)));
	lambda_p::errors::error_list problems;
	lambda_p::binder::list results;
	apply.core (*loop, list, problems, results);
	assert (problems.errors.empty ());
	assert (results.nodes.size () == 1);
	boost::shared_ptr <lambda_p_kernel::number> number (boost::dynamic_pointer_cast <lambda_p_kernel::number> (results [0]));
	assert (number.get () != nullptr);
	assert (number->value == 0);
}

void lambda_p_test::loop_test::run_3 ()
{
	lambda_p::builder inner_builder;
	inner_builder (L"subtract equals not new_value one zero next; subtract equals not value one zero; subtract value one; new_value; equals new_value zero; diff; not diff; next; :;");
	lambda_p::builder outer_builder;
	outer_builder (L"result; loop list routine subtract equals not value one zero; list subtract equals not value one zero; args; loop routine args; results; results ; 1 2 3 result 5 6; :;");
	lambda_p::binder::list list;
	list [0] = boost::shared_ptr <lambda_p_kernel::loop> (new lambda_p_kernel::loop);
	list [1] = boost::shared_ptr <lambda_p::binder::list_binder> (new lambda_p::binder::list_binder);
	boost::shared_ptr <lambda_p_kernel::routine> routine (new lambda_p_kernel::routine (inner_builder.routines.routines->operator[] (0)));
	list [2] = routine;
	list [3] = boost::shared_ptr <lambda_p_kernel::subtract> (new lambda_p_kernel::subtract);
	list [4] = boost::shared_ptr <lambda_p_kernel::equals> (new lambda_p_kernel::equals);
	list [5] = boost::shared_ptr <lambda_p_kernel::not> (new lambda_p_kernel::not);
	list [6] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (5));
	list [7] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (1));
	list [8] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (0));
	lambda_p_kernel::apply apply;
	boost::shared_ptr <lambda_p_kernel::routine> loop (new lambda_p_kernel::routine (outer_builder.routines.routines->operator[] (0)));
	lambda_p::errors::error_list problems;
	lambda_p::binder::list results;
	apply.core (*loop, list, problems, results);
	assert (problems.errors.empty ());
	assert (results.nodes.size () == 1);
	boost::shared_ptr <lambda_p_kernel::number> number (boost::dynamic_pointer_cast <lambda_p_kernel::number> (results [0]));
	assert (number.get () != nullptr);
	assert (number->value == 0);
}

void lambda_p_test::loop_test::run_4 ()
{
	lambda_p::builder inner_builder;
	inner_builder (L"subtract equals not new_value one zero next; subtract equals not value one zero; subtract value one; new_value; equals new_value zero; diff; not diff; next; :;");
	lambda_p::builder outer_builder;
	outer_builder (L"result; loop list routine subtract equals not value one zero; list subtract equals not value one zero; args; loop routine args; results; results ; 1 2 3 result 5 6; :;");
	lambda_p::binder::list list;
	list [0] = boost::shared_ptr <lambda_p_kernel::loop> (new lambda_p_kernel::loop);
	list [1] = boost::shared_ptr <lambda_p::binder::list_binder> (new lambda_p::binder::list_binder);
	boost::shared_ptr <lambda_p_kernel::routine> routine (new lambda_p_kernel::routine (inner_builder.routines.routines->operator[] (0)));
	list [2] = routine;
	list [3] = boost::shared_ptr <lambda_p_kernel::subtract> (new lambda_p_kernel::subtract);
	list [4] = boost::shared_ptr <lambda_p_kernel::equals> (new lambda_p_kernel::equals);
	list [5] = boost::shared_ptr <lambda_p_kernel::not> (new lambda_p_kernel::not);
	list [6] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (10));
	list [7] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (1));
	list [8] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (8));
	lambda_p_kernel::apply apply;
	boost::shared_ptr <lambda_p_kernel::routine> loop (new lambda_p_kernel::routine (outer_builder.routines.routines->operator[] (0)));
	lambda_p::errors::error_list problems;
	lambda_p::binder::list results;
	apply.core (*loop, list, problems, results);
	assert (problems.errors.empty ());
	assert (results.nodes.size () == 1);
	boost::shared_ptr <lambda_p_kernel::number> number (boost::dynamic_pointer_cast <lambda_p_kernel::number> (results [0]));
	assert (number.get () != nullptr);
	assert (number->value == 8);
}