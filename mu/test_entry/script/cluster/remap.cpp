#include <mu/script/cluster/remap_node.h>
#include <mu/script/context.h>
#include <mu/core/cluster.h>
#include <mu/core/routine.h>
#include <mu/core/expression.h>
#include <mu/script/identity/operation.h>
#include <mu/script/fail/operation.h>
#include <mu/core/errors/error_list.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, remap1)
{
	auto cluster (new (GC) mu::core::cluster);
	auto routine (new (GC) mu::core::routine);
	cluster->routines.push_back (routine);
	auto body (new (GC) mu::core::expression);
	routine->body = body;
	auto fail (new (GC) mu::script::fail::operation);
	body->dependencies.push_back (fail);
	auto remap (new (GC) mu::script::cluster::remap_node);
	auto identity (new (GC) mu::script::identity::operation);
	remap->mapping [fail] = identity;
	mu::core::errors::error_list errors;
	mu::script::context context (errors);
	context.push (remap);
	context.push (cluster);
	auto valid (context ());
	EXPECT_EQ (context.working_size (), 1);
	auto cl (dynamic_cast <mu::core::cluster *> (context.working (0)));
	EXPECT_NE (cl, nullptr);
	EXPECT_EQ (cl->routines.size (), 1);
	EXPECT_EQ (cl->routines [0]->body->dependencies.size (), 1);
	EXPECT_EQ (cl->routines [0]->body->dependencies [0], identity);
}