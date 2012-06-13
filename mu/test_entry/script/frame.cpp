#include <mu/script/context.h>
#include <mu/script/frame.h>
#include <mu/core/node.h>

#include <boost/make_shared.hpp>

#include <gtest/gtest.h>

TEST (script_test, frame1)
{
	mu::script::context context;
	EXPECT_EQ (context.stack.size (), 2);
	{
		mu::script::frame frame (context);
	}
	EXPECT_EQ (context.stack.size (), 2);
}

TEST (script_test, frame2)
{
	mu::script::context context;
	EXPECT_EQ (context.stack.size (), 2);
	{
		mu::script::frame frame (context);
		EXPECT_EQ (context.stack.size (), 3);
		context.push (boost::make_shared <mu::core::node> ());
		EXPECT_EQ (context.stack.size (), 4);
	}
	EXPECT_EQ (context.stack.size (), 2);
}

TEST (script_test, frame3)
{
	mu::script::context context;
	EXPECT_EQ (context.stack.size (), 2);
	context.push (boost::make_shared <mu::core::node> ());
	EXPECT_EQ (context.stack.size (), 3);
	{
		mu::script::frame frame (context);
		EXPECT_EQ (context.stack.size (), 4);
		context.push (boost::make_shared <mu::core::node> ());
		EXPECT_EQ (context.stack.size (), 5);
	}
	EXPECT_EQ (context.stack.size (), 3);
}