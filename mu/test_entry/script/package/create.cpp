#include <mu/core/errors/errors.h>
#include <mu/script/package/create.h>
#include <mu/script/package/node.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, package_create1)
{
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::package::create> ());
	auto result (ctx ());
	EXPECT_EQ (result, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto node (boost::dynamic_pointer_cast <mu::script::package::node> (ctx.working (0)));
	EXPECT_NE (node.get (), nullptr);
}