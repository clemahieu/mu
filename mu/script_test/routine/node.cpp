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

#include <boost/make_shared.hpp>

void mu::script_test::routine::node::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
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