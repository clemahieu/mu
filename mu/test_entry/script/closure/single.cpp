#include <mu/core/errors/errors.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/closure/single.h>
#include <mu/script/identity/operation.h>
#include <mu/script/context.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, closure_single1)
{
	std::vector <mu::core::node *, gc_allocator <mu::core::node *>> closed;
	auto n1 (new (GC) mu::core::node);
	closed.push_back (n1);
	mu::core::errors::errors errors (*new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::closure::single (closed, new (GC) mu::script::identity::operation));
	auto n2 (new (GC) mu::core::node);
	ctx.push (n2);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 2);
	EXPECT_EQ (ctx.working (0), n1);
	EXPECT_EQ (ctx.working (1), n2);
}