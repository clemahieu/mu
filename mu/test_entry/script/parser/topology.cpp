#include <gtest/gtest.h>

#include <mu/core/errors/error_list.h>
#include <mu/script/parser/topology.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/runtime/expression.h>

#include <gc_cpp.h>

TEST (script_test, topology1)
{
    mu::core::errors::error_list errors;
	mu::script::runtime::expression root;
    std::vector <mu::script::runtime::expression *> expressions;
	mu::script::parser::topology topology (&root,
        [&expressions]
        (mu::script::runtime::expression * expression_a)
        {
            expressions.push_back (expression_a);
        },
        errors);
    ASSERT_TRUE (expressions.size () == 1);
    EXPECT_TRUE (expressions [0] == &root);
}
/*
TEST (script_test, topology2)
{
	auto routine (new (GC) mu::core::routine);
	auto root (new (GC) mu::core::expression);
	routine->body = root;
	auto c1 (new (GC) mu::core::expression);
	root->dependencies.push_back (c1);
	c1->dependencies.push_back (new (GC) mu::core::parameters);
	auto c2 (new (GC) mu::core::expression);
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

TEST (script_test, topology3)
{
	auto routine (new (GC) mu::core::routine);
	auto root (new (GC) mu::core::expression);
	routine->body = root;
	auto parameters (new (GC) mu::core::expression);
	parameters->dependencies.push_back (new (GC) mu::core::parameters);
	auto r1 (new (GC) mu::core::reference (parameters, 0));
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

TEST (script_test, topology4)
{
	auto routine (new (GC) mu::core::routine);
	auto root (new (GC) mu::core::expression);
	routine->body = root;
	auto expression1 (new (GC) mu::core::expression);
	auto expression2 (new (GC) mu::core::expression);
	expression1->dependencies.push_back (expression2);
	expression2->dependencies.push_back (expression1);
	root->dependencies.push_back (expression1);
	mu::script::topology::core core (routine->body);
	EXPECT_EQ (!core.acyclic, true);
}*/