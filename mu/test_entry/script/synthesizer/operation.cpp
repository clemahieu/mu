#include <mu/core/cluster.h>
#include <mu/script/cluster/node.h>
#include <mu/core/routine.h>
#include <mu/core/expression.h>
#include <mu/core/parameters.h>
#include <mu/script/identity/operation.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/runtime/expression.h>
#include <mu/script/runtime/fixed.h>
#include <mu/script/runtime/reference.h>
#include <mu/script/fail/operation.h>
#include <mu/core/reference.h>
#include <mu/script/synthesizer_synthesizer.h>
#include <mu/script/ast_cluster.h>
#include <mu/script/ast_routine.h>
#include <mu/script/ast_expression.h>
#include <mu/core/errors/error_list.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

// Empty cluster
TEST (script_test, synthesizer_operation1)
{
    mu::core::errors::error_list errors;
    mu::vector <mu::script::cluster::node *> clusters;
    auto clusters_l (&clusters);
    mu::script::synthesizer::synthesizer synthesizer (errors,
                                                      [clusters_l]
                                                      (mu::script::cluster::node * cluster_a)
                                                      {
                                                          clusters_l->push_back (cluster_a);
                                                      });
    auto cluster (new (GC) mu::script::ast::cluster);
    synthesizer (cluster);
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster1 (clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 0);
}

// One routine identity body
TEST (script_test, synthesizer_operation2)
{
    mu::core::errors::error_list errors;
    mu::vector <mu::script::cluster::node *> clusters;
    auto clusters_l (&clusters);
    mu::script::synthesizer::synthesizer synthesizer (errors,
                                                      [clusters_l]
                                                      (mu::script::cluster::node * cluster_a)
                                                      {
                                                          clusters_l->push_back (cluster_a);
                                                      });
    auto cluster (new (GC) mu::script::ast::cluster);
    auto routine1 (new (GC) mu::script::ast::routine);
    cluster->routines.push_back (routine1);
    auto identity (new (GC) mu::script::identity::operation);
    routine1->body->nodes.nodes.push_back (identity);
    synthesizer (cluster);
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster1 (clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    auto routine2 (cluster1->routines [0]);
    ASSERT_TRUE (routine2->expressions.size () == 1);
    auto expression1 (routine2->expressions [0]);
    ASSERT_TRUE (expression1->dependencies.size () == 1);
    auto dependency1 (dynamic_cast <mu::script::runtime::fixed *> (expression1->dependencies [0]));
    ASSERT_TRUE (dependency1 != nullptr);
    EXPECT_TRUE (dependency1->node == identity);
}

// One routine identity of identity
TEST (script_test, synthesizer_operation3)
{
    mu::core::errors::error_list errors;
    mu::vector <mu::script::cluster::node *> clusters;
    auto clusters_l (&clusters);
    mu::script::synthesizer::synthesizer synthesizer (errors,
                                                      [clusters_l]
                                                      (mu::script::cluster::node * cluster_a)
                                                      {
                                                          clusters_l->push_back (cluster_a);
                                                      });
    auto cluster1 (new (GC) mu::script::ast::cluster);
    auto routine1 (new (GC) mu::script::ast::routine);
    cluster1->routines.push_back (routine1);
	auto identity (new (GC) mu::script::identity::operation);
    auto expression1 (new (GC) mu::script::ast::expression);
    routine1->body->nodes.nodes.push_back (identity);
    expression1->nodes.nodes.push_back (identity);
    routine1->body->nodes.nodes.push_back (expression1);
    synthesizer (cluster1);
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster2 (clusters [0]);
    ASSERT_TRUE (cluster2->routines.size () == 1);
    auto routine2 (cluster2->routines [0]);
    ASSERT_TRUE (routine2->expressions.size () == 2);
    auto expression2 (routine2->expressions [0]);
    auto expression3 (routine2->expressions [1]);
    ASSERT_TRUE (expression2->dependencies.size () == 1);
    auto d1 (dynamic_cast <mu::script::runtime::fixed *> (expression2->dependencies [0]));
    ASSERT_TRUE (d1 != nullptr);
    ASSERT_TRUE (d1->node == identity);
    ASSERT_TRUE (expression3->dependencies.size () == 2);
    auto d2 (dynamic_cast <mu::script::runtime::fixed *> (expression3->dependencies [0]));
    ASSERT_TRUE (d2 != nullptr);
    ASSERT_TRUE (d2->node == identity);
    auto d3 (dynamic_cast <mu::script::runtime::reference *> (expression3->dependencies [1]));
    ASSERT_TRUE (d3 != nullptr);
    ASSERT_TRUE (d3->expression == expression2);
}
/*
TEST (script_test, synthesizer_operation4)
{
	mu::core::errors::error_list errors;
	mu::script::context context (errors);
	context.push (new (GC) mu::script::synthesizer::operation);
	auto c (new (GC) mu::core::cluster);
	context.push (c);
	auto routine1 (new (GC) mu::core::routine);
	c->routines.push_back (routine1);
	auto body (new (GC) mu::core::expression);
	routine1->body = body;
	auto expression1 (new (GC) mu::core::expression);
	auto expression2 (new (GC) mu::core::expression);
	expression1->dependencies.push_back (expression2);
	expression2->dependencies.push_back (expression1);
	body->dependencies.push_back (expression1);
	auto valid (context ());
	EXPECT_EQ (!valid, true);
}

TEST (script_test, synthesizer_operation5)
{
	mu::core::errors::error_list errors;
	mu::script::context context (errors);
	context.push (new (GC) mu::script::synthesizer::operation);
	auto c (new (GC) mu::core::cluster);
	context.push (c);
	auto routine1 (new (GC) mu::core::routine);
	c->routines.push_back (routine1);
	auto body (new (GC) mu::core::expression);
	routine1->body = body;
	auto fail (new (GC) mu::script::fail::operation);
	body->dependencies.push_back (fail);
	auto valid (context ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (context.working_size (), 1);
	auto cluster (dynamic_cast <mu::script::cluster::node *> (context.working (0)));
	EXPECT_NE (cluster, nullptr);
	EXPECT_EQ (cluster->routines.size (), 1);
	auto r (cluster->routines [0]);
	EXPECT_EQ (r->expressions.size (), 1);
	auto e (r->expressions [0]);
	EXPECT_EQ (e->dependencies.size (), 1);
	auto d1 (dynamic_cast <mu::script::runtime::fixed *> (e->dependencies [0]));
	EXPECT_NE (d1, nullptr);
	EXPECT_EQ (d1->node, fail);
	context.drop ();
	context.push (r);
	auto valid2 (context ());
	EXPECT_EQ (!valid2, true);
}

TEST (script_test, synthesizer_operation6)
{
	mu::core::errors::error_list errors;
	mu::script::context context (errors);
	context.push (new (GC) mu::script::synthesizer::operation);
	auto c (new (GC) mu::core::cluster);
	context.push (c);
	auto routine1 (new (GC) mu::core::routine);
	c->routines.push_back (routine1);
	auto body (new (GC) mu::core::expression);
	routine1->body = body;
	auto expression (new (GC) mu::core::expression);
	body->dependencies.push_back (new (GC) mu::script::identity::operation);
	body->dependencies.push_back (expression);
	expression->dependencies.push_back (new (GC) mu::script::identity::operation);
	auto valid (context ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (context.working_size (), 1);
	auto cluster (dynamic_cast <mu::script::cluster::node *> (context.working (0)));
	EXPECT_NE (cluster, nullptr);
	EXPECT_EQ (cluster->routines.size (), 1);
	auto r (cluster->routines [0]);
	context.drop ();
	context.push (r);
	auto valid2 (context ());
	EXPECT_EQ (valid2, true);
	EXPECT_EQ (context.working_size (), 0);
}

TEST (script_test, synthesizer_operation7)
{
	mu::core::errors::error_list errors;
	mu::script::context context (errors);
	context.push (new (GC) mu::script::synthesizer::operation);
	auto c (new (GC) mu::core::cluster);
	context.push (c);
	auto routine1 (new (GC) mu::core::routine);
	c->routines.push_back (routine1);
	auto body (new (GC) mu::core::expression);
	routine1->body = body;
	auto expression (new (GC) mu::core::expression);
	expression->dependencies.push_back (new (GC) mu::script::identity::operation);
	auto n1 (new (GC) mu::core::node);
	expression->dependencies.push_back (n1);
	body->dependencies.push_back (new (GC) mu::script::identity::operation);
	body->dependencies.push_back (new (GC) mu::core::reference (expression, 0));
	auto valid (context ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (context.working_size (), 1);
	auto cluster (dynamic_cast <mu::script::cluster::node *> (context.working (0)));
	EXPECT_NE (cluster, nullptr);
	EXPECT_EQ (cluster->routines.size (), 1);
	auto r (cluster->routines [0]);
	context.drop ();
	context.push (r);
	auto valid2 (context ());
	EXPECT_EQ (valid2, true);
	EXPECT_EQ (context.working_size (), 1);
	EXPECT_EQ (context.working (0), n1);
}

TEST (script_test, synthesizer_operation8)
{
	mu::core::errors::error_list errors;
	mu::script::context context (errors);
	context.push (new (GC) mu::script::synthesizer::operation);
	auto c (new (GC) mu::core::cluster);
	context.push (c);
	auto routine1 (new (GC) mu::core::routine);
	c->routines.push_back (routine1);
	auto body (new (GC) mu::core::expression);
	routine1->body = body;
	auto expression (new (GC) mu::core::expression);
	expression->dependencies.push_back (new (GC) mu::script::identity::operation);
	auto n1 (new (GC) mu::core::node);
	expression->dependencies.push_back (n1);
	auto expression2 (new (GC) mu::core::expression);
	expression2->dependencies.push_back (new (GC) mu::script::identity::operation);
	expression2->dependencies.push_back (new (GC) mu::core::reference (expression, 0));
	body->dependencies.push_back (new (GC) mu::script::identity::operation);
	body->dependencies.push_back (new (GC) mu::core::reference (expression, 0));
	body->dependencies.push_back (expression2);
	auto valid (context ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (context.working_size (), 1);
	auto cluster (dynamic_cast <mu::script::cluster::node *> (context.working (0)));
	EXPECT_NE (cluster, nullptr);
	EXPECT_EQ (cluster->routines.size (), 1);
	auto r (cluster->routines [0]);
	context.drop ();
	context.push (r);
	auto valid2 (context ());
	EXPECT_EQ (valid2, true);
	EXPECT_EQ (context.working_size (), 2);
	EXPECT_EQ (context.working (0), n1);
	EXPECT_EQ (context.working (1), n1);
}

TEST (script_test, synthesizer_operation9)
{
	mu::core::errors::error_list errors;
	mu::script::context context (errors);
	context.push (new (GC) mu::script::synthesizer::operation);
	auto c (new (GC) mu::core::cluster);
	context.push (c);
	auto routine1 (new (GC) mu::core::routine);
	c->routines.push_back (routine1);
	auto body (new (GC) mu::core::expression);
	routine1->body = body;
	auto expression (new (GC) mu::core::expression);
	expression->dependencies.push_back (new (GC) mu::script::identity::operation);
	auto n1 (new (GC) mu::core::node);
	expression->dependencies.push_back (n1);
	auto expression2 (new (GC) mu::core::expression);
	expression2->dependencies.push_back (new (GC) mu::script::identity::operation);
	expression2->dependencies.push_back (new (GC) mu::core::reference (expression, 0));
	body->dependencies.push_back (new (GC) mu::script::identity::operation);
	body->dependencies.push_back (expression2);
	body->dependencies.push_back (new (GC) mu::core::reference (expression, 0));
	auto valid (context ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (context.working_size (), 1);
	auto cluster (dynamic_cast <mu::script::cluster::node *> (context.working (0)));
	EXPECT_NE (cluster, nullptr);
	EXPECT_EQ (cluster->routines.size (), 1);
	auto r (cluster->routines [0]);
	context.drop ();
	context.push (r);
	auto valid2 (context ());
	EXPECT_EQ (valid2, true);
	EXPECT_EQ (context.working_size (), 2);
	EXPECT_EQ (context.working (0), n1);
	EXPECT_EQ (context.working (1), n1);
}

TEST (script_test, synthesizer_operation10)
{
	mu::core::errors::error_list errors;
	mu::script::context context (errors);
	context.push (new (GC) mu::script::synthesizer::operation);
	auto c (new (GC) mu::core::cluster);
	context.push (c);
	auto routine1 (new (GC) mu::core::routine);
	c->routines.push_back (routine1);
	auto routine2 (new (GC) mu::core::routine);
	c->routines.push_back (routine2);
	auto body (new (GC) mu::core::expression);
	routine1->body = body;
	body->dependencies.push_back (new (GC) mu::script::identity::operation);
	body->dependencies.push_back (routine2);
	auto body2 (new (GC) mu::core::expression);
	routine2->body = body;
	body2->dependencies.push_back (new (GC) mu::script::fail::operation);
	auto valid (context ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (context.working_size (), 1);
	auto cluster (dynamic_cast <mu::script::cluster::node *> (context.working (0)));
	EXPECT_NE (cluster, nullptr);
	EXPECT_EQ (cluster->routines.size (), 2);
	auto r (cluster->routines [0]);
	context.drop ();
	context.push (r);
	auto valid2 (context ());
	EXPECT_EQ (valid2, true);
}*/