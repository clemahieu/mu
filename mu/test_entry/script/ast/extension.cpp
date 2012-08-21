#include <mu/core/expression.h>
#include <mu/io/ast/expression.h>
#include <mu/io/ast/identifier.h>
#include <mu/io/ast/cluster.h>
#include <mu/script/builder.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/context.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/api.h>
#include <mu/script/extensions/node.h>
#include <mu/io/source.h>
#include <mu/script/cluster/node.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

/*
TEST (script_test, extension1)
{
    ASSERT_TRUE (false);
	mu::script::builder builder (mu::script::api::core ()->extensions);
	mu::io::process (builder, U"[~ .ast []]");
	ASSERT_TRUE (builder.errors.errors.empty ());
	ASSERT_TRUE (builder.clusters.size () == 1);
	ASSERT_TRUE (builder.clusters [0]->routines.size () == 1);
	auto routine (builder.clusters [0]->routines [0]);
	mu::script::context ctx (builder.errors);
	ctx.push (routine);
	auto valid (ctx ());
	EXPECT_TRUE (valid);
	EXPECT_TRUE (ctx.working_size () == 1);
	auto cl (dynamic_cast <mu::io::ast::cluster *> (ctx.working (0)));
	EXPECT_TRUE (cl != nullptr);
	EXPECT_TRUE (cl->expressions.size () == 0);
}

TEST (script_test, extension2)
{
    ASSERT_TRUE (false);
	mu::script::builder builder (mu::script::api::core ()->extensions);
	mu::io::process (builder, U"[~ .ast thing]");
	EXPECT_TRUE (!builder.errors.errors.empty ());
	EXPECT_TRUE (builder.clusters.size () == 0);
}

TEST (script_test, extension3)
{
    ASSERT_TRUE (false);
	mu::script::builder builder (mu::script::api::core ()->extensions);
	mu::io::process (builder, U"[~ .ast [[]]]");
	ASSERT_TRUE (builder.errors.errors.empty ());
	ASSERT_TRUE (builder.clusters.size () == 0);
	ASSERT_TRUE (builder.clusters [0]->routines.size () == 1);
	auto routine (builder.clusters [0]->routines [0]);
	mu::script::context ctx (builder.errors);
	ctx.push (routine);
	auto valid (ctx ());
	EXPECT_TRUE (valid);
	EXPECT_TRUE (ctx.working_size () == 1);
	auto cl (dynamic_cast <mu::io::ast::cluster *> (ctx.working (0)));
	EXPECT_TRUE (cl != nullptr);
	EXPECT_TRUE (cl->expressions.size () == 1);
	auto expression (cl->expressions [0]);
}*/