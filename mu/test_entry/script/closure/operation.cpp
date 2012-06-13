#include <mu/script/closure/operation.h>
#include <mu/script/identity/operation.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/closure/hole.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

#include <gtest/gtest.h>

TEST (script_test, closure_operation1)
{
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::closure::operation> (0, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation)));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 0);
}

TEST (script_test, closure_operation2)
{
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::closure::operation> (1, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation)));
	auto node (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (node);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	EXPECT_EQ (ctx.working (0), node);
}

TEST (script_test, closure_operation3)
{
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::closure::operation> (2, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation)));
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (n1);
	auto n2 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (n2);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 2);
	EXPECT_EQ (ctx.working (0), n1);
	EXPECT_EQ (ctx.working (1), n2);
}

TEST (script_test, closure_operation4)
{
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::closure::operation> (2, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation)));
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (n1);
	auto n2 (boost::shared_ptr <mu::core::node> (new mu::script::closure::hole));
	ctx.push (n2);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	assert (ctx.working_size () == 1);
	auto result (boost::dynamic_pointer_cast <mu::script::closure::operation> (ctx.working (0)));
	EXPECT_NE (result.get (), nullptr);
	ctx.drop ();
	ctx.push (result);
	auto n3 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (n3);
	auto valid2 (ctx ());
	EXPECT_EQ (valid2, true);
	EXPECT_EQ (ctx.working_size (), 2);
	EXPECT_EQ (ctx.working (0), n1);
	EXPECT_EQ (ctx.working (1), n3);
}

TEST (script_test, closure_operation5)
{
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::closure::operation> (2, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation)));
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::script::closure::hole));
	ctx.push (n1);
	auto n2 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (n2);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto result (boost::dynamic_pointer_cast <mu::script::closure::operation> (ctx.working (0)));
	EXPECT_NE (result.get (), nullptr);
	ctx.drop ();
	ctx.push (result);
	auto n3 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (n3);
	auto valid2 (ctx ());
	EXPECT_EQ (valid2, true);
	EXPECT_EQ (ctx.working_size (), 2);
	EXPECT_EQ (ctx.working (0), n3);
	EXPECT_EQ (ctx.working (1), n2);
}