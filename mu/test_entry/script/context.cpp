#include <mu/script/context.h>
#include <mu/core/node.h>
#include <mu/script/identity/operation.h>
#include <mu/core/routine.h>
#include <mu/core/expression.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, context1)
{
	mu::script::context context;
	EXPECT_EQ (context.stack.size (), 2);
	EXPECT_EQ (context.frame_begin, 2);
	EXPECT_EQ (context.base_begin, 0);
	EXPECT_EQ (context.base_end, 2);
	EXPECT_EQ (context.locals_size (), 0);
	EXPECT_EQ (context.parameters_size (), 0);
	EXPECT_EQ (context.working_size (), 0);
	EXPECT_EQ (context.locals_begin (), context.locals_end ());
	EXPECT_EQ (context.parameters_begin (), context.parameters_end ());
	EXPECT_EQ (context.working_begin (), context.working_end ());
}

TEST (script_test, context2)
{
	mu::script::context context;
	auto working1 (new (GC) mu::core::node);
	context.push (working1);
	EXPECT_EQ (context.stack.size (), 3);
	EXPECT_EQ (context.frame_begin, 2);
	EXPECT_EQ (context.base_begin, 0);
	EXPECT_EQ (context.base_end, 2);
	EXPECT_EQ (context.locals_size (), 0);
	EXPECT_EQ (context.parameters_size (), 0);
	EXPECT_EQ (context.working_size (), 1);
	EXPECT_EQ (context.working (0), working1);
	EXPECT_NE (context.working_begin (), context.working_end ());
	EXPECT_EQ (++context.working_begin (), context.working_end ());
	EXPECT_NE (--++context.working_begin (), context.working_end ());
	EXPECT_EQ (++--++context.working_begin (), context.working_end ());
}

TEST (script_test, context3)
{
	mu::script::context context;
	context.push (new (GC) mu::core::node);
	context.drop ();
	EXPECT_EQ (context.stack.size (), 2);
	EXPECT_EQ (context.frame_begin, 2);
	EXPECT_EQ (context.base_begin, 0);
	EXPECT_EQ (context.base_end, 2);
	EXPECT_EQ (context.locals_size (), 0);
	EXPECT_EQ (context.parameters_size (), 0);
	EXPECT_EQ (context.working_size (), 0);
}

TEST (script_test, context4)
{
	mu::script::context context;
	auto local1 (new (GC) mu::core::node);
	context.push (local1);
	context.slide ();
	EXPECT_EQ (context.stack.size (), 3);
	EXPECT_EQ (context.frame_begin, 3);
	EXPECT_EQ (context.base_begin, 0);
	EXPECT_EQ (context.base_end, 2);
	EXPECT_EQ (context.locals_size (), 1);
	EXPECT_EQ (context.parameters_size (), 0);
	EXPECT_EQ (context.working_size (), 0);
	EXPECT_EQ (context.locals (0), local1);
	EXPECT_NE (context.locals_begin (), context.locals_end ());
	EXPECT_EQ (++context.locals_begin (), context.locals_end ());
}

TEST (script_test, context5)
{
	mu::script::context context;
	context.enter ();
	EXPECT_EQ (context.stack.size (), 4);
	EXPECT_EQ (context.frame_begin, 4);
	EXPECT_EQ (context.base_begin, 2);
	EXPECT_EQ (context.base_end, 4);
	EXPECT_EQ (context.locals_size (), 0);
	EXPECT_EQ (context.parameters_size (), 0);
	EXPECT_EQ (context.working_size (), 0);
}

TEST (script_test, context6)
{
	mu::script::context context;
	context.enter ();
	context.leave ();
	EXPECT_EQ (context.stack.size (), 2);
	EXPECT_EQ (context.frame_begin, 2);
	EXPECT_EQ (context.base_begin, 0);
	EXPECT_EQ (context.base_end, 2);
	EXPECT_EQ (context.locals_size (), 0);
	EXPECT_EQ (context.parameters_size (), 0);
	EXPECT_EQ (context.working_size (), 0);
}

TEST (script_test, context7)
{
	mu::script::context context;
	auto arg1 (new (GC) mu::core::node);
	context.push (arg1);
	context.enter ();
	EXPECT_EQ (context.stack.size (), 5);
	EXPECT_EQ (context.frame_begin, 5);
	EXPECT_EQ (context.base_begin, 2);
	EXPECT_EQ (context.base_end, 5);
	EXPECT_EQ (context.locals_size (), 0);
	EXPECT_EQ (context.parameters_size (), 1);
	EXPECT_EQ (context.working_size (), 0);
	EXPECT_EQ (context.parameters (0), arg1);
	EXPECT_NE (context.parameters_begin (), context.parameters_end ());
	EXPECT_EQ (++context.parameters_begin (), context.parameters_end ());
}

TEST (script_test, context8)
{
	mu::script::context context;
	auto arg1 (new (GC) mu::core::node);
	context.push (arg1);
	context.enter ();
	auto res1 (new (GC) mu::core::node);
	context.push (res1);
	EXPECT_EQ (context.working_size (), 1);
	EXPECT_EQ (*context.working_begin (), res1);
	context.leave ();
	EXPECT_EQ (context.working_size (), 1);
	EXPECT_EQ (*context.working_begin (), res1);
}

TEST (script_test, context9)
{
	mu::script::context context;
	auto arg1 (new (GC) mu::script::identity::operation);
	context.push (arg1);
	auto arg2 (new (GC) mu::script::identity::operation);
	context.push (arg2);
	auto valid (context ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (context.working_size (), 1);
	EXPECT_EQ (context.working (0), arg2);
}

TEST (script_test, context10)
{
	mu::script::context context;
	auto valid (context ());
	EXPECT_EQ (!valid, true);
	EXPECT_EQ (context.working_size (), 0);
}

TEST (script_test, context11)
{
	mu::script::context context;
	auto arg1 (new (GC) mu::core::node);
	context.push (arg1);
	auto arg2 (new (GC) mu::script::identity::operation);
	context.push (arg2);
	auto valid (context ());
	EXPECT_EQ (!valid, true);
	EXPECT_EQ (context.working_size (), 0);
}

TEST (script_test, context12)
{
	mu::script::context context;
	context.reserve (1);
	EXPECT_EQ (context.stack.size (), 3);
	EXPECT_EQ (context.frame_begin, 3);
	EXPECT_EQ (context.base_begin, 0);
	EXPECT_EQ (context.base_end, 2);
	EXPECT_EQ (context.locals_size (), 1);
	EXPECT_EQ (context.parameters_size (), 0);
	EXPECT_EQ (context.working_size (), 0);
}

TEST (script_test, context13)
{
	mu::script::context context;
	context.reserve (1);
	auto val1 (new (GC) mu::core::node);
	context.push (val1);
	context.assign (context.locals_begin (), context.working_begin (), context.working_end ());
	EXPECT_EQ (context.locals (0), context.working (0));
}

/*
mu::core::routine isn't an operation anymore
TEST (script_test, context14)
{
	mu::script::context context;
	auto expression (boost::make_shared <mu::core::expression> ());
	expression->dependencies.push_back (boost::make_shared <mu::script::identity::operation> ());
	auto val1 (boost::make_shared <mu::core::routine> ());
	context.push (val1);
	auto valid (context ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (context.working_size (), 0);
}*/