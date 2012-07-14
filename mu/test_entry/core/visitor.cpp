#include <mu/test_entry/core/test_visitor.h>
#include <mu/core/expression.h>
#include <mu/core/node.h>
#include <mu/core/reference.h>
#include <mu/core/routine.h>
#include <mu/core/parameters.h>
#include <mu/core/cluster.h>

#include <boost/shared_ptr.hpp>

#include <gtest/gtest.h>

TEST (core_test, visitor1)
{
	boost::shared_ptr <mu::core_test::test_visitor> visitor (new mu::core_test::test_visitor);
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
	boost::shared_ptr <mu::core_test::test_visitor> vis (new mu::core_test::test_visitor);	
	boost::shared_ptr <mu::core::visitor> visitor (vis);
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
	boost::shared_ptr <mu::core_test::test_visitor> vis (new mu::core_test::test_visitor);	
	boost::shared_ptr <mu::core::visitor> visitor (vis);
	mu::core::cluster * cluster (new mu::core::cluster);
	mu::core::expression * expression (new mu::core::expression);
	mu::core::parameters * parameters (new mu::core::parameters);
	mu::core::node * node (new mu::core::node);
	mu::core::reference * reference (new mu::core::reference (nullptr, 0));
	mu::core::routine * routine (new mu::core::routine);
	(*cluster) (visitor.get ());
	(*expression) (visitor.get ());	
	(*parameters) (visitor.get ());
	(*node) (visitor.get ());
	(*reference) (visitor.get ());
	(*routine) (visitor.get ());
	EXPECT_EQ (vis->clusters.size (), 1);
	EXPECT_EQ (vis->expressions.size (), 1);
	EXPECT_EQ (vis->parameters.size (), 1);
	EXPECT_EQ (vis->nodes.size (), 1);
	EXPECT_EQ (vis->references.size (), 1);
	EXPECT_EQ (vis->routines.size (), 1);
}