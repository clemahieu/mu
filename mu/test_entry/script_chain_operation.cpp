#include <mu/core/errors/error_list.h>
#include <mu/script/loop.h>
#include <mu/test_entry/script_chain_ten_count.h>
#include <mu/script/integer_node.h>
#include <mu/script/context.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, loop1)
{
	auto operation (new (GC) mu::script_test::chain::ten_count);
	auto count (new (GC) mu::script::integer::node (50));
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::loop);
	ctx.push (operation);
	ctx.push (count);
	auto valid (ctx ());
	EXPECT_TRUE (valid);
	EXPECT_TRUE (ctx.working_size () == 1);
	auto result (dynamic_cast <mu::script::integer::node *> (ctx.working (0)));
	EXPECT_TRUE (result->value == 40);
}