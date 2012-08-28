#include <mu/script/times_operation.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/integer_subtract.h>
#include <mu/script/integer_node.h>
#include <mu/script/builder.h>
#include <mu/io/source.h>
#include <mu/script/context.h>
#include <mu/script/api.h>
#include <mu/script/parser_scope_node.h>
#include <mu/script/identity_operation.h>
#include <mu/script/cluster_node.h>
#include <mu/script/runtime_routine.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, times_operation1)
{
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::times::operation);
	auto n1 (new (GC) mu::script::integer::node (0));
	ctx.push (n1);
	auto n2 (new (GC) mu::script::integer::subtract);
	ctx.push (n2);
	auto n3 (new (GC) mu::script::integer::node (5));
	ctx.push (n3);
	auto n4 (new (GC) mu::script::integer::node (1));
	ctx.push (n4);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 2);
	EXPECT_EQ (ctx.working (0), n3);
	EXPECT_EQ (ctx.working (1), n4);
}

TEST (script_test, DISABLED_times_operation2)
{
    assert (false);/*
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	auto expression (new (GC) mu::core::expression);
	expression->dependencies.push_back (new (GC) mu::core::parameters);
	auto routine (new (GC) mu::core::routine (expression));
	ctx.push (new (GC) mu::script::times::operation);
	ctx.push (new (GC) mu::script::integer::node (10));
	ctx.push (new (GC) mu::script::identity::operation);
	auto n1 (new (GC) mu::core::node);
	ctx.push (n1);
	auto n2 (new (GC) mu::core::node);
	ctx.push (n2);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 2);
	EXPECT_EQ (ctx.working (0), n1);
	EXPECT_EQ (ctx.working (1), n2);*/
}

TEST (script_test, times_operation3)
{
    auto core (mu::script::api::core ());
	mu::script::builder builder (boost::get <1> (core), boost::get <0> (core)->extensions);
	mu::io::process (builder, U"[1 [subtract number amount] [~ subtract [subtract number amount] amount]]");
	EXPECT_TRUE (builder.errors.errors.empty ());
    builder.errors.print (std::wcout);
	mu::script::context ctx (builder.errors);
	ctx.push (new (GC) mu::script::times::operation);
	ASSERT_TRUE (builder.clusters.size () == 1);
	ASSERT_TRUE (builder.clusters [0]->routines.size () == 1);
	auto n1 (new (GC) mu::script::integer::node (2));
	ctx.push (n1);
	auto n2 (builder.clusters [0]->routines [mu::string (U"1")]);
	ctx.push (n2);
	auto n3 (new (GC) mu::script::integer::subtract);
	ctx.push (n3);
	auto n4 (new (GC) mu::script::integer::node (5));
	ctx.push (n4);
	auto n5 (new (GC) mu::script::integer::node (1));
	ctx.push (n5);
	auto valid (ctx ());
    builder.errors.print (std::wcout);
	EXPECT_TRUE (valid);
	EXPECT_TRUE (ctx.working_size () == 3);
	auto r1 (dynamic_cast <mu::script::integer::subtract *> (ctx.working (0)));
	EXPECT_TRUE (r1 != nullptr);
	auto r2 (dynamic_cast <mu::script::integer::node *> (ctx.working (1)));
	EXPECT_TRUE (r2 != nullptr);
	EXPECT_TRUE (r2->value == 3);
	auto r3 (dynamic_cast <mu::script::integer::node *> (ctx.working (2)));
	EXPECT_TRUE (r3 != nullptr);
	EXPECT_TRUE (r3->value == 1);
}