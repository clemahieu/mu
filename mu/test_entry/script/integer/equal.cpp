#include <mu/core/errors/errors.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/integer/equal.h>
#include <mu/script/integer/node.h>
#include <mu/script/bool_c/node.h>
#include <mu/script/context.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, integer_equal1)
{
	mu::core::errors::errors errors (*new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::integer::equal);
	ctx.push (new (GC) mu::script::integer::node (3));
	ctx.push (new (GC) mu::script::integer::node (5));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto result (dynamic_cast <mu::script::bool_c::node *> (ctx.working (0)));
	EXPECT_NE (result, nullptr);
	EXPECT_EQ (result->value, false);
}

TEST (script_test, integer_equal2)
{
	mu::core::errors::errors errors (*new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::integer::equal);
	ctx.push (new (GC) mu::script::integer::node (3));
	ctx.push (new (GC) mu::script::integer::node (3));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto result (dynamic_cast <mu::script::bool_c::node *> (ctx.working (0)));
	EXPECT_NE (result, nullptr);
	EXPECT_EQ (result->value, true);
}

TEST (script_test, integer_equal3)
{
	mu::core::errors::errors errors (*new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::integer::equal);
	ctx.push (new (GC) mu::script::integer::node (3));
	ctx.push (new (GC) mu::core::node);
	auto valid (ctx ());
	EXPECT_EQ (!valid, true);
}