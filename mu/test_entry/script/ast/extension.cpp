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

TEST (script_test, extension1)
{
	mu::script::builder builder (mu::script::api::core ()->extensions);
	builder (L"[~ .ast []]");
	builder ();
	EXPECT_EQ (builder.errors->errors.empty (), true);
	auto cluster (builder.cluster);
	EXPECT_NE (cluster, nullptr);
	EXPECT_EQ (cluster->routines.size (), 1);
	auto routine (cluster->routines [0]);
	mu::script::context ctx (mu::core::errors::errors (builder.errors));
	ctx.push (routine);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto cl (dynamic_cast <mu::io::ast::cluster *> (ctx.working (0)));
	EXPECT_NE (cl, nullptr);
	EXPECT_EQ (cl->expressions.size (), 0);
}

TEST (script_test, extension2)
{
	mu::script::builder builder (mu::script::api::core ()->extensions);
	builder (L"[~ .ast thing]");
	builder ();
	EXPECT_EQ (!builder.errors->errors.empty (), true);
	EXPECT_EQ (builder.cluster, nullptr);
}

TEST (script_test, extension3)
{
	mu::script::builder builder (mu::script::api::core ()->extensions);
	builder (L"[~ .ast [[]]]");
	builder ();
	EXPECT_EQ (builder.errors->errors.empty (), true);
	auto cluster (builder.cluster);
	EXPECT_NE (cluster, nullptr);
	EXPECT_EQ (cluster->routines.size (), 1);
	auto routine (cluster->routines [0]);
	mu::script::context ctx (mu::core::errors::errors (builder.errors));
	ctx.push (routine);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto cl (dynamic_cast <mu::io::ast::cluster *> (ctx.working (0)));
	EXPECT_NE (cl, nullptr);
	EXPECT_EQ (cl->expressions.size (), 1);
	auto expression (cl->expressions [0]);
}