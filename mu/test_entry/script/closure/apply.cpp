#include <mu/core/errors/error_list.h>
#include <mu/core/errors/errors.h>
#include <mu/script/closure/operation.h>
#include <mu/script/closure/apply.h>
#include <mu/script/identity/operation.h>
#include <mu/script/context.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, apply1)
{
	mu::core::errors::errors errors (*new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::closure::apply);
	auto c1 (new (GC) mu::script::closure::operation (1, new (GC) mu::script::identity::operation));
	auto n1 (new (GC) mu::core::node);
	ctx.push (c1);
	ctx.push (n1);
	auto result (ctx ());
	EXPECT_EQ (result, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto c2 (dynamic_cast <mu::script::closure::operation *> (ctx.working (0)));
	EXPECT_NE (c2, nullptr);
	ctx.drop ();
	ctx.push (c2);
	auto result2 (ctx ());
	EXPECT_EQ (result2, true);
	EXPECT_EQ (ctx.working_size (), 1);
	EXPECT_EQ (ctx.working (0), n1);
}