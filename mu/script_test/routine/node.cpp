#include <mu/script_test/routine/node.h>

#include <mu/core/expression.h>
#include <mu/core/parameters.h>
#include <mu/core/reference.h>
#include <mu/script/routine/node.h>
#include <mu/script/context.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/values/operation.h>
#include <mu/script/routine/locals.h>
#include <mu/script/identity/operation.h>
#include <mu/script/fail/operation.h>
#include <mu/core/routine.h>

#include <boost/make_shared.hpp>

void mu::script_test::routine::node::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
	run_7 ();
	run_8 ();
	run_9 ();
	run_10 ();
	run_11 ();
}

void mu::script_test::routine::node::run_1 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	context.push (boost::make_shared <mu::script::routine::node> ());
	context.push (boost::make_shared <mu::script::routine::locals> ());
	context.push (boost::make_shared <mu::script::values::operation> ());
	context.push (boost::make_shared <mu::core::expression> ());
	auto valid (context ());
	assert (!valid);
	assert (context.working_size () == 0);
}

void mu::script_test::routine::node::run_2 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	context.push (boost::make_shared <mu::script::routine::node> ());
	context.push (boost::make_shared <mu::script::routine::locals> ());
	context.push (boost::make_shared <mu::script::values::operation> ());
	auto expression (boost::make_shared <mu::core::expression> ());
	context.push (expression);
	expression->dependencies.push_back (boost::make_shared <mu::script::identity::operation> ());
	auto valid (context ());
	assert (valid);
	assert (context.working_size () == 0);
}

void mu::script_test::routine::node::run_3 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	context.push (boost::make_shared <mu::script::routine::node> ());
	context.push (boost::make_shared <mu::script::routine::locals> ());
	context.push (boost::make_shared <mu::script::values::operation> ());
	auto expression (boost::make_shared <mu::core::expression> ());
	context.push (expression);
	expression->dependencies.push_back (boost::make_shared <mu::script::identity::operation> ());
	expression->dependencies.push_back (boost::make_shared <mu::core::node> ());
	auto valid (context ());
	assert (valid);
	assert (context.working_size () == 1);
	assert (context.working (0) == expression->dependencies [1]);
}

void mu::script_test::routine::node::run_4 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	context.push (boost::make_shared <mu::script::routine::node> ());
	context.push (boost::make_shared <mu::script::routine::locals> ());
	context.push (boost::make_shared <mu::script::values::operation> ());
	auto expression (boost::make_shared <mu::core::expression> ());
	context.push (expression);
	auto expression1 (boost::make_shared <mu::core::expression> ());
	auto expression2 (boost::make_shared <mu::core::expression> ());
	expression1->dependencies.push_back (expression2);
	expression2->dependencies.push_back (expression1);
	expression->dependencies.push_back (expression1);
	expression->dependencies.push_back (expression2);
	auto valid (context ());
	assert (!valid);
	assert (context.working_size () == 0);
}

void mu::script_test::routine::node::run_5 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	context.push (boost::make_shared <mu::script::routine::node> ());
	context.push (boost::make_shared <mu::script::routine::locals> ());
	context.push (boost::make_shared <mu::script::values::operation> ());
	auto expression (boost::make_shared <mu::core::expression> ());
	expression->dependencies.push_back (boost::make_shared <mu::script::fail::operation> ());
	context.push (expression);
	auto valid (context ());
	assert (!valid);
	assert (context.working_size () == 0);
}

void mu::script_test::routine::node::run_6 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	context.push (boost::make_shared <mu::script::routine::node> ());
	context.push (boost::make_shared <mu::script::routine::locals> ());
	context.push (boost::make_shared <mu::script::values::operation> ());
	auto expression (boost::make_shared <mu::core::expression> ());
	auto expression1 (boost::make_shared <mu::core::expression> ());
	expression->dependencies.push_back (boost::make_shared <mu::script::identity::operation> ());
	expression->dependencies.push_back (expression1);
	expression1->dependencies.push_back (boost::make_shared <mu::script::identity::operation> ());
	context.push (expression);
	auto valid (context ());
	assert (valid);
	assert (context.working_size () == 0);
}

void mu::script_test::routine::node::run_7 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	context.push (boost::make_shared <mu::script::routine::node> ());
	context.push (boost::make_shared <mu::script::routine::locals> ());
	context.push (boost::make_shared <mu::script::values::operation> ());
	auto expression (boost::make_shared <mu::core::expression> ());
	auto expression1 (boost::make_shared <mu::core::expression> ());
	expression->dependencies.push_back (boost::make_shared <mu::script::identity::operation> ());
	expression->dependencies.push_back (expression1);
	expression1->dependencies.push_back (boost::make_shared <mu::script::identity::operation> ());
	context.push (expression);
	auto valid (context ());
	assert (valid);
	assert (context.working_size () == 0);
}

void mu::script_test::routine::node::run_8 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	auto expression (boost::make_shared <mu::core::expression> ());
	auto expression1 (boost::make_shared <mu::core::expression> ());
	auto routine (boost::make_shared <mu::core::routine> (expression));
	expression->dependencies.push_back (boost::make_shared <mu::script::identity::operation> ());
	expression->dependencies.push_back (expression1);
	expression1->dependencies.push_back (boost::make_shared <mu::core::parameters> ());
	context.push (routine);
	auto arg1 (boost::make_shared <mu::core::node> ());
	context.push (arg1);
	auto valid (context ());
	assert (valid);
	assert (context.working_size () == 1);
	assert (arg1 == context.working (0));
}

void mu::script_test::routine::node::run_9 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	auto expression (boost::make_shared <mu::core::expression> ());
	auto expression1 (boost::make_shared <mu::core::expression> ());
	auto n1 (boost::make_shared <mu::core::node> ());
	expression1->dependencies.push_back (boost::make_shared <mu::script::identity::operation> ());
	expression1->dependencies.push_back (n1);
	auto reference (boost::make_shared <mu::core::reference> (expression1, 0));
	expression->dependencies.push_back (boost::make_shared <mu::script::identity::operation> ());
	expression->dependencies.push_back (reference);
	auto routine (boost::make_shared <mu::core::routine> (expression));
	context.push (routine);
	auto valid (context ());
	assert (valid);
	assert (context.working_size () == 1);
	assert (context.working (0) == n1);
}

void mu::script_test::routine::node::run_10 ()
{
	//"[[:~; 1] ~ 1 [~ 1]]"
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	context.stack.reserve (100);
	auto expression1 (boost::make_shared <mu::core::expression> ());
	expression1->dependencies.push_back (boost::make_shared <mu::core::parameters> ());
	auto expression2 (boost::make_shared <mu::core::expression> ());
	expression2->dependencies.push_back (boost::make_shared <mu::script::identity::operation> ());
	expression2->dependencies.push_back (boost::make_shared <mu::core::reference> (expression1, 0));
	auto expression3 (boost::make_shared <mu::core::expression> ());
	expression3->dependencies.push_back (boost::make_shared <mu::script::identity::operation> ());
	expression3->dependencies.push_back (boost::make_shared <mu::core::reference> (expression1, 0));
	expression3->dependencies.push_back (expression2);
	auto routine (boost::make_shared <mu::core::routine> (expression3));
	context.push (routine);
	auto n1 (boost::make_shared <mu::core::node> ());
	context.push (n1);
	auto valid (context ());
	assert (valid);
	assert (context.working_size () == 2);
}

void mu::script_test::routine::node::run_11 ()
{
	//"[[:~; 1] ~ [~ 1] 1]"
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	context.stack.reserve (100);
	auto expression1 (boost::make_shared <mu::core::expression> ());
	expression1->dependencies.push_back (boost::make_shared <mu::core::parameters> ());
	auto expression2 (boost::make_shared <mu::core::expression> ());
	expression2->dependencies.push_back (boost::make_shared <mu::script::identity::operation> ());
	expression2->dependencies.push_back (boost::make_shared <mu::core::reference> (expression1, 0));
	auto expression3 (boost::make_shared <mu::core::expression> ());
	expression3->dependencies.push_back (boost::make_shared <mu::script::identity::operation> ());
	expression3->dependencies.push_back (expression2);
	expression3->dependencies.push_back (boost::make_shared <mu::core::reference> (expression1, 0));
	auto routine (boost::make_shared <mu::core::routine> (expression3));
	context.push (routine);
	auto n1 (boost::make_shared <mu::core::node> ());
	context.push (n1);
	auto valid (context ());
	assert (valid);
	assert (context.working_size () == 2);
}