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

void lambda_p_test::loop_test::run ()
{
	run_1 ();
}

void lambda_p_test::loop_test::run_1 ()
{
	lambda_p::builder inner_builder;
	inner_builder (L"subtract equals new_value one zero next; subtract equals value one zero; subtract value one; new_value; equals new_value zero; next; :;");
	lambda_p::builder outer_builder;
	outer_builder (L"; loop list routine subtract equals value one zero; list subtract equals value one zero; args; loop routine args; results; :;");
	lambda_p::binder::list list;
	list [0] = boost::shared_ptr <lambda_p_kernel::loop> (new lambda_p_kernel::loop);
	list [1] = boost::shared_ptr <lambda_p::binder::list_binder> (new lambda_p::binder::list_binder);
	boost::shared_ptr <lambda_p_kernel::routine> routine (new lambda_p_kernel::routine (inner_builder.routines.routines->operator[] (0)));
	list [2] = routine;
	list [3] = boost::shared_ptr <lambda_p_kernel::subtract> (new lambda_p_kernel::subtract);
	list [4] = boost::shared_ptr <lambda_p_kernel::equals> (new lambda_p_kernel::equals);
	list [5] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (1));
	list [6] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (1));
	list [7] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (0));
	lambda_p_kernel::apply apply;
	boost::shared_ptr <lambda_p_kernel::routine> loop (new lambda_p_kernel::routine (outer_builder.routines.routines->operator[] (0)));
	lambda_p::errors::error_list problems;
	lambda_p::binder::list results;
	apply.core (*loop, list, problems, results);
	assert (problems.errors.empty ());
}