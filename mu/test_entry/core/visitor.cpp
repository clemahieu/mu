#include <mu/test_entry/core/test_visitor.h>
#include <mu/core/expression.h>
#include <mu/core/node.h>
#include <mu/core/reference.h>
#include <mu/core/routine.h>
#include <mu/core/parameters.h>
#include <mu/core/cluster.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (core_test, visitor1)
{
	auto visitor (new (GC) mu::core_test::test_visitor);
	mu::core::cluster * cluster (nullptr);
	mu::core::expression * expression (nullptr);
	mu::core::parameters * parameters (nullptr);
	mu::core::node * node (nullptr);
	mu::core::reference * reference (nullptr);
	mu::core::routine * routine (nullptr);
	(*visitor) (cluster);
	(*visitor) (expression);	
	(*visitor) (parameters);
	(*visitor) (node);	
	(*visitor) (reference);
	(*visitor) (routine);
	EXPECT_EQ (visitor->clusters.size (), 1);
	EXPECT_EQ (visitor->expressions.size (), 1);
	EXPECT_EQ (visitor->parameters.size (), 1);
	EXPECT_EQ (visitor->nodes.size (), 1);
	EXPECT_EQ (visitor->references.size (), 1);
	EXPECT_EQ (visitor->routines.size (), 1);
}

TEST (core_test, visitor2)
{
	auto vis (new (GC) mu::core_test::test_visitor);	
    mu::core::visitor * visitor (vis);
	mu::core::cluster * cluster (nullptr);
	mu::core::expression * expression (nullptr);
	mu::core::parameters * parameters (nullptr);
	mu::core::node * node (nullptr);
	mu::core::reference * reference (nullptr);
	mu::core::routine * routine (nullptr);
	(*visitor) (cluster);
	(*visitor) (expression);	
	(*visitor) (parameters);
	(*visitor) (node);	
	(*visitor) (reference);
	(*visitor) (routine);
	EXPECT_EQ (vis->clusters.size (), 1);
	EXPECT_EQ (vis->expressions.size (), 1);
	EXPECT_EQ (vis->parameters.size (), 1);
	EXPECT_EQ (vis->nodes.size (), 1);
	EXPECT_EQ (vis->references.size (), 1);
	EXPECT_EQ (vis->routines.size (), 1);
}

TEST (core_test, visitor3)
{
	auto vis (new (GC) mu::core_test::test_visitor);	
    mu::core::visitor * visitor (vis);
	mu::core::cluster * cluster (new (GC) mu::core::cluster);
	mu::core::expression * expression (new (GC) mu::core::expression);
	mu::core::parameters * parameters (new (GC) mu::core::parameters);
	mu::core::node * node (new (GC) mu::core::node);
	mu::core::reference * reference (new (GC) mu::core::reference (nullptr, 0));
	mu::core::routine * routine (new (GC) mu::core::routine);
	(*cluster) (visitor);
	(*expression) (visitor);	
	(*parameters) (visitor);
	(*node) (visitor);
	(*reference) (visitor);
	(*routine) (visitor);
	EXPECT_EQ (vis->clusters.size (), 1);
	EXPECT_EQ (vis->expressions.size (), 1);
	EXPECT_EQ (vis->parameters.size (), 1);
	EXPECT_EQ (vis->nodes.size (), 1);
	EXPECT_EQ (vis->references.size (), 1);
	EXPECT_EQ (vis->routines.size (), 1);
}