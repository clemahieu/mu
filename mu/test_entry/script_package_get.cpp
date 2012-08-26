#include <mu/core/errors/error_list.h>
#include <mu/script/package_get.h>
#include <mu/script/package_node.h>
#include <mu/script/string_node.h>
#include <mu/script/context.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, package_get1)
{
	mu::core::errors::error_list errors;
	auto data (new (GC) mu::script::package::node);
	auto name (new (GC) mu::script::string::node (mu::string (U"test")));
	auto node (new (GC) mu::core::node);
	data->items [mu::string (U"test")] = node;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::package::get);
	ctx.push (data);
	ctx.push (name);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	EXPECT_EQ (ctx.working (0), node);
}