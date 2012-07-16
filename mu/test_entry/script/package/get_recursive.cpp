#include <mu/core/errors/errors.h>
#include <mu/script/package/get_recursive.h>
#include <mu/script/package/node.h>
#include <mu/script/string/node.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/context.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, package_get_recursive1)
{
	auto package (new (GC) mu::script::package::node);
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::package::get_recursive);
	ctx.push (package);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	EXPECT_EQ (ctx.working (0), package);
}

TEST (script_test, package_get_recursive2)
{
	auto package (new (GC) mu::script::package::node);
	auto n1 (new (GC) mu::core::node);
	package->items [mu::string (U"a")] = n1;
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::package::get_recursive);
	ctx.push (package);
	ctx.push (new (GC) mu::script::string::node (mu::string (U"a")));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	EXPECT_EQ (ctx.working (0), n1);
}

TEST (script_test, package_get_recursive3)
{
	auto package (new (GC) mu::script::package::node);
	auto package1 (new (GC) mu::script::package::node);
	auto n1 (new (GC) mu::core::node);
	package->items [mu::string (U"a")] = package1;
	package1->items [mu::string (U"b")] = n1;
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::package::get_recursive);
	ctx.push (package);
	ctx.push (new (GC) mu::script::string::node (mu::string (U"a")));
	ctx.push (new (GC) mu::script::string::node (mu::string (U"b")));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	EXPECT_EQ (ctx.working (0), n1);
}