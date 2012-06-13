#include <mu/core/errors/error_list.h>
#include <mu/core/routine.h>
#include <mu/core/expression.h>
#include <mu/core/reference.h>
#include <mu/script/topology/core.h>
#include <mu/core/parameters.h>
#include <mu/script/topology/node.h>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <gtest/gtest.h>

TEST (script_test, topology_core1)
{
	auto routine (boost::make_shared <mu::core::routine> ());
	auto root (boost::make_shared <mu::core::expression> ());
	routine->body = root;
	auto parameters (boost::make_shared <mu::core::expression> ());
	root->dependencies.push_back (parameters);
	parameters->dependencies.push_back (boost::make_shared <mu::core::parameters> ());
	mu::script::topology::core order (routine->body);
	auto i (order.topology->expressions.begin ());
	EXPECT_EQ (*i, parameters);
	++i;
	EXPECT_EQ (*i, root);
	++i;
	EXPECT_EQ (i, order.topology->expressions.end ());
	EXPECT_EQ (order.acyclic, true);
}

TEST (script_test, topology_core2)
{
	auto routine (boost::make_shared <mu::core::routine> ());
	auto root (boost::make_shared <mu::core::expression> ());
	routine->body = root;
	auto c1 (boost::make_shared <mu::core::expression> ());
	root->dependencies.push_back (c1);
	c1->dependencies.push_back (boost::make_shared <mu::core::parameters> ());
	auto c2 (boost::make_shared <mu::core::expression> ());
	root->dependencies.push_back (c2);
	c2->dependencies.push_back (c1);
	mu::script::topology::core order (routine->body);
	auto i (order.topology->expressions.begin ());
	EXPECT_EQ (*i, c1);
	++i;
	EXPECT_EQ (*i, c2);
	++i;
	EXPECT_EQ (*i, root);
	++i;
	EXPECT_EQ (i, order.topology->expressions.end ());
	EXPECT_EQ (order.acyclic, true);
}

TEST (script_test, topology_core3)
{
	auto routine (boost::make_shared <mu::core::routine> ());
	auto root (boost::make_shared <mu::core::expression> ());
	routine->body = root;
	auto parameters (boost::make_shared <mu::core::expression> ());
	parameters->dependencies.push_back (boost::make_shared <mu::core::parameters> ());
	auto r1 (boost::make_shared <mu::core::reference> (parameters, 0));
	root->dependencies.push_back (r1);
	mu::script::topology::core order (routine->body);
	auto i (order.topology->expressions.begin ());
	EXPECT_EQ (*i, parameters);
	++i;
	EXPECT_EQ (*i, root);
	++i;
	EXPECT_EQ (i, order.topology->expressions.end ());
	EXPECT_EQ (order.acyclic, true);
}

TEST (script_test, topology_core4)
{
	auto routine (boost::make_shared <mu::core::routine> ());
	auto root (boost::make_shared <mu::core::expression> ());
	routine->body = root;
	auto expression1 (boost::make_shared <mu::core::expression> ());
	auto expression2 (boost::make_shared <mu::core::expression> ());
	expression1->dependencies.push_back (expression2);
	expression2->dependencies.push_back (expression1);
	root->dependencies.push_back (expression1);
	mu::script::topology::core core (routine->body);
	EXPECT_EQ (!core.acyclic, true);
}