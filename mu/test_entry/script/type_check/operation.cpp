#include <mu/core/errors/error_list.h>
#include <mu/script/type_check/operation.h>
#include <mu/script/identity/operation.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, type_check_operation1)
{
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	auto identity (new (GC) mu::script::identity::operation);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::type_check::operation <> (identity));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
}

TEST (script_test, type_check_operation2)
{
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	auto identity (new (GC) mu::script::identity::operation);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::type_check::operation <> (identity));
	ctx.push (new (GC) mu::script::identity::operation);
	auto valid (ctx ());
	EXPECT_EQ (!valid, true);
	EXPECT_EQ (ctx.working_size (), 0);
}

TEST (script_test, type_check_operation3)
{
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	auto identity (new (GC) mu::script::identity::operation);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::type_check::operation <mu::script::identity::operation> (identity));
	ctx.push (new (GC) mu::script::identity::operation);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
}

TEST (script_test, type_check_operation4)
{
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	auto identity (new (GC) mu::script::identity::operation);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::type_check::operation <mu::script::identity::operation> (identity));
	auto valid (ctx ());
	EXPECT_EQ (!valid, true);
	EXPECT_EQ (ctx.working_size (), 0);
}

TEST (script_test, type_check_operation5)
{
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	auto identity (new (GC) mu::script::identity::operation);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::type_check::operation <mu::script::identity::operation> (identity));
	ctx.push (new (GC) mu::core::node);
	auto valid (ctx ());
	EXPECT_EQ (!valid, true);
	EXPECT_EQ (ctx.working_size (), 0);
}

TEST (script_test, type_check_operation6)
{
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	auto identity (new (GC) mu::script::identity::operation);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::type_check::operation <mu::core::node, mu::core::node> (identity));
	ctx.push (new (GC) mu::core::node);
	ctx.push (new (GC) mu::core::node);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 2);
}