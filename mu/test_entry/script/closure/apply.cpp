#include <mu/core/errors/error_list.h>
#include <mu/core/errors/errors.h>
#include <mu/script/closure/operation.h>
#include <mu/script/closure/apply.h>
#include <mu/script/identity/operation.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, apply1)
{
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::closure::apply> ());
	auto c1 (boost::shared_ptr <mu::core::node> (new mu::script::closure::operation (1, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation))));
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (c1);
	ctx.push (n1);
	auto result (ctx ());
	EXPECT_EQ (result, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto c2 (boost::dynamic_pointer_cast <mu::script::closure::operation> (ctx.working (0)));
	EXPECT_NE (c2.get (), nullptr);
	ctx.drop ();
	ctx.push (c2);
	auto result2 (ctx ());
	EXPECT_EQ (result2, true);
	EXPECT_EQ (ctx.working_size (), 1);
	EXPECT_EQ (ctx.working (0), n1);
}