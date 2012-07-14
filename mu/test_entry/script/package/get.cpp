#include <mu/core/errors/errors.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/package/get.h>
#include <mu/script/package/node.h>
#include <mu/script/string/node.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, package_get1)
{
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	auto data (new (GC) mu::script::package::node);
	auto name (new (GC) mu::script::string::node (std::wstring (L"test")));
	auto node (new (GC) mu::core::node);
	data->items [std::wstring (L"test")] = node;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::package::get);
	ctx.push (data);
	ctx.push (name);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	EXPECT_EQ (ctx.working (0), node);
}