#include <gtest/gtest.h>

#include <mu/script/context.h>
#include <mu/script/runtime_if_expression.h>
#include <mu/script/runtime_locals.h>
#include <mu/script/runtime_routine.h>
#include <mu/script/runtime_definite_expression.h>
#include <mu/script/identity.h>
#include <mu/script/bool_c_node.h>
#include <mu/script/runtime_fixed.h>
#include <mu/script/fail_operation.h>

#include <gc_cpp.h>

// Success of true branch
TEST (script_test, if_expression1)
{
    auto identity (new (GC) mu::script::identity);
    auto fail (new (GC) mu::script::fail::operation);
    auto routine (new (GC) mu::script::runtime::routine);
    auto body (new (GC) mu::script::runtime::definite_expression);
    routine->expressions.push_back (body);
    auto if_l (new (GC) mu::script::runtime::if_expression);
    body->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    body->dependencies.push_back (if_l);
    auto node1 (new (GC) mu::core::node);
    auto value (new (GC) mu::script::bool_c::node (true));
    auto predicate (new (GC) mu::script::runtime::definite_expression);
    if_l->predicate = predicate;
    predicate->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    predicate->dependencies.push_back (new (GC) mu::script::runtime::fixed (value));
    auto true_branch (new (GC) mu::script::runtime::definite_expression);
    if_l->true_branch = true_branch;
    true_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    true_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (node1));
    auto false_branch (new (GC) mu::script::runtime::definite_expression);
    if_l->false_branch = false_branch;
    false_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (fail));
    mu::script::context context;
    context.push (routine);
    auto valid (context ());
    ASSERT_TRUE (valid);
    ASSERT_TRUE (context.working_size () == 1);
    ASSERT_TRUE (context.working(0) == node1);
}

// Success of false branch
TEST (script_test, if_expression2)
{
    auto identity (new (GC) mu::script::identity);
    auto fail (new (GC) mu::script::fail::operation);
    auto routine (new (GC) mu::script::runtime::routine);
    auto body (new (GC) mu::script::runtime::definite_expression);
    routine->expressions.push_back (body);
    auto if_l (new (GC) mu::script::runtime::if_expression);
    body->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    body->dependencies.push_back (if_l);
    auto node2 (new (GC) mu::core::node);
    auto value (new (GC) mu::script::bool_c::node (false));
    auto predicate (new (GC) mu::script::runtime::definite_expression);
    if_l->predicate = predicate;
    predicate->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    predicate->dependencies.push_back (new (GC) mu::script::runtime::fixed (value));
    auto true_branch (new (GC) mu::script::runtime::definite_expression);
    if_l->true_branch = true_branch;
    true_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (fail));
    auto false_branch (new (GC) mu::script::runtime::definite_expression);
    if_l->false_branch = false_branch;
    false_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    false_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (node2));
    mu::script::context context;
    context.push (routine);
    auto valid (context ());
    ASSERT_TRUE (valid);
    ASSERT_TRUE (context.working_size () == 1);
    ASSERT_TRUE (context.working(0) == node2);
}

// Failure in false branch
TEST (script_test, if_expression3)
{
    auto identity (new (GC) mu::script::identity);
    auto fail (new (GC) mu::script::fail::operation);
    auto routine (new (GC) mu::script::runtime::routine);
    auto body (new (GC) mu::script::runtime::definite_expression);
    routine->expressions.push_back (body);
    auto if_l (new (GC) mu::script::runtime::if_expression);
    body->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    body->dependencies.push_back (if_l);
    auto node1 (new (GC) mu::core::node);
    auto value (new (GC) mu::script::bool_c::node (false));
    auto predicate (new (GC) mu::script::runtime::definite_expression);
    if_l->predicate = predicate;
    predicate->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    predicate->dependencies.push_back (new (GC) mu::script::runtime::fixed (value));
    auto true_branch (new (GC) mu::script::runtime::definite_expression);
    if_l->true_branch = true_branch;
    true_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    true_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (node1));
    auto false_branch (new (GC) mu::script::runtime::definite_expression);
    if_l->false_branch = false_branch;
    false_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (fail));
    mu::script::context context;
    context.push (routine);
    auto valid (context ());
    ASSERT_TRUE (!valid);
}

// Failure in true branch
TEST (script_test, if_expression4)
{
    auto identity (new (GC) mu::script::identity);
    auto fail (new (GC) mu::script::fail::operation);
    auto routine (new (GC) mu::script::runtime::routine);
    auto body (new (GC) mu::script::runtime::definite_expression);
    routine->expressions.push_back (body);
    auto if_l (new (GC) mu::script::runtime::if_expression);
    body->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    body->dependencies.push_back (if_l);
    auto node2 (new (GC) mu::core::node);
    auto value (new (GC) mu::script::bool_c::node (true));
    auto predicate (new (GC) mu::script::runtime::definite_expression);
    if_l->predicate = predicate;
    predicate->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    predicate->dependencies.push_back (new (GC) mu::script::runtime::fixed (value));
    auto true_branch (new (GC) mu::script::runtime::definite_expression);
    if_l->true_branch = true_branch;
    true_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (fail));
    auto false_branch (new (GC) mu::script::runtime::definite_expression);
    if_l->false_branch = false_branch;
    false_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (identity));
    false_branch->dependencies.push_back (new (GC) mu::script::runtime::fixed (node2));
    mu::script::context context;
    context.push (routine);
    auto valid (context ());
    ASSERT_TRUE (!valid);
}