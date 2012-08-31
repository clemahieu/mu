#include <gtest/gtest.h>

#include <mu/script/context.h>
#include <mu/script/runtime_if_clause.h>
#include <mu/script/runtime_locals.h>
#include <mu/script/runtime_routine.h>
#include <mu/script/runtime_expression.h>
#include <mu/script/identity_operation.h>
#include <mu/script/bool_c_node.h>
#include <mu/script/runtime_fixed.h>
#include <mu/script/fail_operation.h>

#include <gc_cpp.h>

// Success of true branch
TEST (script_test, if_clause1)
{
    auto identity (new (GC) mu::script::identity::operation);
    auto fail (new (GC) mu::script::fail::operation);
    auto routine (new (GC) mu::script::runtime::routine);
    auto body (new (GC) mu::script::runtime::expression);
    routine->expressions.push_back (body);
    auto if_l (new (GC) mu::script::runtime::if_clause);
    body->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    body->dependencies.push_back (if_l);
    auto node1 (new (GC) mu::core::node);
    auto value (new (GC) mu::script::bool_c::node (true));
    if_l->predicate = new (GC) mu::script::runtime::expression;
    if_l->predicate->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    if_l->predicate->dependencies.push_back (new (GC) mu::script::runtime::fixed (value));
    if_l->true_branch = new (GC) mu::script::runtime::expression;
    if_l->true_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    if_l->true_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (node1));
    if_l->false_branch = new (GC) mu::script::runtime::expression;
    if_l->false_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (fail));
    mu::script::context context;
    context.push (routine);
    auto valid (context ());
    ASSERT_TRUE (valid);
    ASSERT_TRUE (context.working_size () == 1);
    ASSERT_TRUE (context.working(0) == node1);
}

// Success of false branch
TEST (script_test, if_clause2)
{
    auto identity (new (GC) mu::script::identity::operation);
    auto fail (new (GC) mu::script::fail::operation);
    auto routine (new (GC) mu::script::runtime::routine);
    auto body (new (GC) mu::script::runtime::expression);
    routine->expressions.push_back (body);
    auto if_l (new (GC) mu::script::runtime::if_clause);
    body->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    body->dependencies.push_back (if_l);
    auto node2 (new (GC) mu::core::node);
    auto value (new (GC) mu::script::bool_c::node (false));
    if_l->predicate = new (GC) mu::script::runtime::expression;
    if_l->predicate->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    if_l->predicate->dependencies.push_back (new (GC) mu::script::runtime::fixed (value));
    if_l->true_branch = new (GC) mu::script::runtime::expression;
    if_l->true_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (fail));
    if_l->false_branch = new (GC) mu::script::runtime::expression;
    if_l->false_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    if_l->false_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (node2));
    mu::script::context context;
    context.push (routine);
    auto valid (context ());
    ASSERT_TRUE (valid);
    ASSERT_TRUE (context.working_size () == 1);
    ASSERT_TRUE (context.working(0) == node2);
}

// Failure in false branch
TEST (script_test, if_clause3)
{
    auto identity (new (GC) mu::script::identity::operation);
    auto fail (new (GC) mu::script::fail::operation);
    auto routine (new (GC) mu::script::runtime::routine);
    auto body (new (GC) mu::script::runtime::expression);
    routine->expressions.push_back (body);
    auto if_l (new (GC) mu::script::runtime::if_clause);
    body->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    body->dependencies.push_back (if_l);
    auto node1 (new (GC) mu::core::node);
    auto value (new (GC) mu::script::bool_c::node (false));
    if_l->predicate = new (GC) mu::script::runtime::expression;
    if_l->predicate->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    if_l->predicate->dependencies.push_back (new (GC) mu::script::runtime::fixed (value));
    if_l->true_branch = new (GC) mu::script::runtime::expression;
    if_l->true_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    if_l->true_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (node1));
    if_l->false_branch = new (GC) mu::script::runtime::expression;
    if_l->false_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (fail));
    mu::script::context context;
    context.push (routine);
    auto valid (context ());
    ASSERT_TRUE (!valid);
}

// Failure in true branch
TEST (script_test, if_clause4)
{
    auto identity (new (GC) mu::script::identity::operation);
    auto fail (new (GC) mu::script::fail::operation);
    auto routine (new (GC) mu::script::runtime::routine);
    auto body (new (GC) mu::script::runtime::expression);
    routine->expressions.push_back (body);
    auto if_l (new (GC) mu::script::runtime::if_clause);
    body->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    body->dependencies.push_back (if_l);
    auto node2 (new (GC) mu::core::node);
    auto value (new (GC) mu::script::bool_c::node (true));
    if_l->predicate = new (GC) mu::script::runtime::expression;
    if_l->predicate->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    if_l->predicate->dependencies.push_back (new (GC) mu::script::runtime::fixed (value));
    if_l->true_branch = new (GC) mu::script::runtime::expression;
    if_l->true_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (fail));
    if_l->false_branch = new (GC) mu::script::runtime::expression;
    if_l->false_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    if_l->false_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (node2));
    mu::script::context context;
    context.push (routine);
    auto valid (context ());
    ASSERT_TRUE (!valid);
}