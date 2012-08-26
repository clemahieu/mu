#include <mu/script/closure_operation.h>
#include <mu/script/identity_operation.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/closure_hole.h>
#include <mu/script/context.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, closure_operation1)
{
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::closure::operation (0, new (GC) mu::script::identity::operation));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 0);
}

TEST (script_test, closure_operation2)
{
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::closure::operation (1, new (GC) mu::script::identity::operation));
	auto node (new (GC) mu::core::node);
	ctx.push (node);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	EXPECT_EQ (ctx.working (0), node);
}

TEST (script_test, closure_operation3)
{
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::closure::operation (2, new (GC) mu::script::identity::operation));
	auto n1 (new (GC) mu::core::node);
	ctx.push (n1);
	auto n2 (new (GC) mu::core::node);
	ctx.push (n2);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 2);
	EXPECT_EQ (ctx.working (0), n1);
	EXPECT_EQ (ctx.working (1), n2);
}

TEST (script_test, closure_operation4)
{
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::closure::operation (2, new (GC) mu::script::identity::operation));
	auto n1 (new (GC) mu::core::node);
	ctx.push (n1);
	auto n2 (new (GC) mu::script::closure::hole);
	ctx.push (n2);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	assert (ctx.working_size () == 1);
	auto result (dynamic_cast <mu::script::closure::operation *> (ctx.working (0)));
	EXPECT_NE (result, nullptr);
	ctx.drop ();
	ctx.push (result);
	auto n3 (new (GC) mu::core::node);
	ctx.push (n3);
	auto valid2 (ctx ());
	EXPECT_EQ (valid2, true);
	EXPECT_EQ (ctx.working_size (), 2);
	EXPECT_EQ (ctx.working (0), n1);
	EXPECT_EQ (ctx.working (1), n3);
}

TEST (script_test, closure_operation5)
{
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::closure::operation (2, new (GC) mu::script::identity::operation));
	auto n1 (new (GC) mu::script::closure::hole);
	ctx.push (n1);
	auto n2 (new (GC) mu::core::node);
	ctx.push (n2);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto result (dynamic_cast <mu::script::closure::operation *> (ctx.working (0)));
	EXPECT_NE (result, nullptr);
	ctx.drop ();
	ctx.push (result);
	auto n3 (new (GC) mu::core::node);
	ctx.push (n3);
	auto valid2 (ctx ());
	EXPECT_EQ (valid2, true);
	EXPECT_EQ (ctx.working_size (), 2);
	EXPECT_EQ (ctx.working (0), n3);
	EXPECT_EQ (ctx.working (1), n2);
}