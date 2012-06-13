#include <mu/core/errors/errors.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/closure/single.h>
#include <mu/script/identity/operation.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

#include <gtest/gtest.h>

TEST (script_test, closure_single1)
{
	std::vector <boost::shared_ptr <mu::core::node>> closed;
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	closed.push_back (n1);
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::closure::single> (closed, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation)));
	auto n2 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (n2);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 2);
	EXPECT_EQ (ctx.working (0), n1);
	EXPECT_EQ (ctx.working (1), n2);
}