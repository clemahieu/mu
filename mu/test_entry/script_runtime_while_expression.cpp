#include <gtest/gtest.h>

#include <mu/script/runtime_while_expression.h>
#include <mu/script/context.h>
#include <mu/script/bool_c_node.h>
#include <mu/script/integer_node.h>
#include <mu/script/integer_equal.h>
#include <mu/script/integer_subtract.h>
#include <mu/script/identity.h>
#include <mu/script/runtime_fixed.h>
#include <mu/script/runtime_routine.h>
#include <mu/script/runtime_definite_expression.h>
#include <mu/script/runtime_parameter.h>
#include <mu/script/runtime_reference.h>
#include <mu/core/errors/error_target.h>
#include <mu/script/runtime_locals.h>

#include <gc_cpp.h>

TEST (script_test, while_expression1)
{
    mu::script::context context;
    mu::script::runtime::while_expression while_l;
    mu::script::integer::equal equal;
    while_l.predicate.push_back (new (GC) mu::script::runtime::fixed (&equal));
    mu::script::identity identity;
    mu::script::runtime::routine routine;
    while_l.body.push_back (new (GC) mu::script::runtime::fixed (&routine));
    mu::script::runtime::definite_expression expression1;
    routine.expressions.push_back (&expression1);
    mu::script::integer::subtract sub;
    expression1.dependencies.push_back (new (GC) mu::script::runtime::fixed (&sub));
    expression1.dependencies.push_back (new (GC) mu::script::runtime::parameter (1));
    mu::script::integer::node one (1);
    expression1.dependencies.push_back (new (GC) mu::script::runtime::fixed (&one));
    mu::script::runtime::definite_expression expression2;
    routine.expressions.push_back (&expression2);
    expression2.dependencies.push_back (new (GC) mu::script::runtime::fixed (&identity));
    expression2.dependencies.push_back (new (GC) mu::script::runtime::parameter (0));
    expression2.dependencies.push_back (new (GC) mu::script::runtime::reference (&expression1));
    while_l.arguments.push_back (new (GC) mu::script::runtime::fixed (&one));
    while_l.arguments.push_back (new (GC) mu::script::runtime::fixed (&one));
    context.push (&while_l);
    mu::script::runtime::locals local (0);
    context.push (&local);
    auto valid (context ());
    context.errors.print (std::wcerr);
    ASSERT_TRUE (valid);
    ASSERT_TRUE (context.working_size () == 2);
    auto integer1 (dynamic_cast <mu::script::integer::node *> (context.working (0)));
    ASSERT_TRUE (integer1 != nullptr);
    ASSERT_TRUE (integer1->value == 1);
    auto integer2 (dynamic_cast <mu::script::integer::node *> (context.working (1)));
    ASSERT_TRUE (integer2 != nullptr);
    ASSERT_TRUE (integer2->value == 0);
}

TEST (script_test, while_expression2)
{
    mu::script::context context;
    mu::script::runtime::while_expression while_l;
    mu::script::integer::equal equal;
    while_l.predicate.push_back (new (GC) mu::script::runtime::fixed (&equal));
    mu::script::identity identity;
    mu::script::runtime::routine routine;
    while_l.body.push_back (new (GC) mu::script::runtime::fixed (&routine));
    mu::script::runtime::definite_expression expression1;
    routine.expressions.push_back (&expression1);
    mu::script::integer::subtract sub;
    expression1.dependencies.push_back (new (GC) mu::script::runtime::fixed (&sub));
    expression1.dependencies.push_back (new (GC) mu::script::runtime::parameter (1));
    mu::script::integer::node one (1);
    expression1.dependencies.push_back (new (GC) mu::script::runtime::fixed (&one));
    mu::script::runtime::definite_expression expression2;
    routine.expressions.push_back (&expression2);
    expression2.dependencies.push_back (new (GC) mu::script::runtime::fixed (&identity));
    expression2.dependencies.push_back (new (GC) mu::script::runtime::parameter (0));
    expression2.dependencies.push_back (new (GC) mu::script::runtime::reference (&expression1));
    mu::script::integer::node two (2);
    while_l.arguments.push_back (new (GC) mu::script::runtime::fixed (&two));
    while_l.arguments.push_back (new (GC) mu::script::runtime::fixed (&one));
    context.push (&while_l);
    mu::script::runtime::locals local (0);
    context.push (&local);
    auto valid (context ());
    context.errors.print (std::wcerr);
    ASSERT_TRUE (valid);
    ASSERT_TRUE (context.working_size () == 2);
    auto integer1 (dynamic_cast <mu::script::integer::node *> (context.working (0)));
    ASSERT_TRUE (integer1 != nullptr);
    ASSERT_TRUE (integer1->value == 2);
    auto integer2 (dynamic_cast <mu::script::integer::node *> (context.working (1)));
    ASSERT_TRUE (integer2 != nullptr);
    ASSERT_TRUE (integer2->value == 1);
}

// Fail, return fewer results than arguments
TEST (script_test, while_expression3)
{
    mu::script::context context;
    mu::script::runtime::while_expression while_l;
    mu::script::integer::equal equal;
    while_l.predicate.push_back (new (GC) mu::script::runtime::fixed (&equal));
    mu::script::identity identity;
    mu::script::runtime::routine routine;
    while_l.body.push_back (new (GC) mu::script::runtime::fixed (&routine));
    mu::script::runtime::definite_expression expression1;
    routine.expressions.push_back (&expression1);
    mu::script::integer::subtract sub;
    expression1.dependencies.push_back (new (GC) mu::script::runtime::fixed (&sub));
    expression1.dependencies.push_back (new (GC) mu::script::runtime::parameter (1));
    mu::script::integer::node one (1);
    expression1.dependencies.push_back (new (GC) mu::script::runtime::fixed (&one));
    mu::script::runtime::definite_expression expression2;
    routine.expressions.push_back (&expression2);
    expression2.dependencies.push_back (new (GC) mu::script::runtime::fixed (&identity));
    expression2.dependencies.push_back (new (GC) mu::script::runtime::parameter (0));
    while_l.arguments.push_back (new (GC) mu::script::runtime::fixed (&one));
    while_l.arguments.push_back (new (GC) mu::script::runtime::fixed (&one));
    context.push (&while_l);
    mu::script::runtime::locals local (0);
    context.push (&local);
    auto valid (context ());
    ASSERT_TRUE (!valid);
}

// Fail, return more results than arguments
TEST (script_test, while_expression4)
{
    mu::script::context context;
    mu::script::runtime::while_expression while_l;
    mu::script::integer::equal equal;
    while_l.predicate.push_back (new (GC) mu::script::runtime::fixed (&equal));
    mu::script::identity identity;
    mu::script::runtime::routine routine;
    while_l.body.push_back (new (GC) mu::script::runtime::fixed (&routine));
    mu::script::runtime::definite_expression expression1;
    routine.expressions.push_back (&expression1);
    mu::script::integer::subtract sub;
    expression1.dependencies.push_back (new (GC) mu::script::runtime::fixed (&sub));
    expression1.dependencies.push_back (new (GC) mu::script::runtime::parameter (1));
    mu::script::integer::node one (1);
    expression1.dependencies.push_back (new (GC) mu::script::runtime::fixed (&one));
    mu::script::runtime::definite_expression expression2;
    routine.expressions.push_back (&expression2);
    expression2.dependencies.push_back (new (GC) mu::script::runtime::fixed (&identity));
    expression2.dependencies.push_back (new (GC) mu::script::runtime::parameter (0));
    expression2.dependencies.push_back (new (GC) mu::script::runtime::reference (&expression1));
    expression2.dependencies.push_back (new (GC) mu::script::runtime::parameter (0));
    while_l.arguments.push_back (new (GC) mu::script::runtime::fixed (&one));
    while_l.arguments.push_back (new (GC) mu::script::runtime::fixed (&one));
    context.push (&while_l);
    mu::script::runtime::locals local (0);
    context.push (&local);
    auto valid (context ());
    ASSERT_TRUE (!valid);
}

// Fail, check doesn't return bool
TEST (script_test, while_expression5)
{
    mu::script::context context;
    mu::script::runtime::while_expression while_l;
    mu::script::identity equal;
    while_l.predicate.push_back (new (GC) mu::script::runtime::fixed (&equal));
    mu::script::identity identity;
    mu::script::runtime::routine routine;
    while_l.body.push_back (new (GC) mu::script::runtime::fixed (&routine));
    mu::script::runtime::definite_expression expression1;
    routine.expressions.push_back (&expression1);
    mu::script::integer::subtract sub;
    expression1.dependencies.push_back (new (GC) mu::script::runtime::fixed (&sub));
    expression1.dependencies.push_back (new (GC) mu::script::runtime::parameter (1));
    mu::script::integer::node one (1);
    expression1.dependencies.push_back (new (GC) mu::script::runtime::fixed (&one));
    mu::script::runtime::definite_expression expression2;
    routine.expressions.push_back (&expression2);
    expression2.dependencies.push_back (new (GC) mu::script::runtime::fixed (&identity));
    expression2.dependencies.push_back (new (GC) mu::script::runtime::parameter (0));
    expression2.dependencies.push_back (new (GC) mu::script::runtime::reference (&expression1));
    while_l.arguments.push_back (new (GC) mu::script::runtime::fixed (&one));
    while_l.arguments.push_back (new (GC) mu::script::runtime::fixed (&one));
    context.push (&while_l);
    mu::script::runtime::locals local (0);
    context.push (&local);
    auto valid (context ());
    ASSERT_TRUE (!valid);
}