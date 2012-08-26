#include <gtest/gtest.h>

#include <mu/core/errors/error_list.h>
#include <mu/script/parser_topology.h>
#include <mu/script/runtime_routine.h>
#include <mu/script/runtime_expression.h>
#include <mu/script/runtime_selection.h>

#include <gc_cpp.h>

// Topology of one
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
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (expressions.size () == 1);
    EXPECT_TRUE (expressions [0] == &root);
}

// Simple nested
TEST (script_test, topology2)
{
    mu::core::errors::error_list errors;
	mu::script::runtime::expression root;
    mu::script::runtime::expression e1;
    root.dependencies.push_back (&e1);
    std::vector <mu::script::runtime::expression *> expressions;
	mu::script::parser::topology topology (&root,
                                           [&expressions]
                                           (mu::script::runtime::expression * expression_a)
                                           {
                                               expressions.push_back (expression_a);
                                           },
                                           errors);
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (expressions.size () == 2);
    EXPECT_TRUE (expressions [0] == &e1);
    EXPECT_TRUE (expressions [1] == &root);
}

// Double nest
TEST (script_test, topology3)
{
    mu::core::errors::error_list errors;
	mu::script::runtime::expression root;
    mu::script::runtime::expression e1;
    mu::script::runtime::expression e2;
    root.dependencies.push_back (&e1);
    e1.dependencies.push_back (&e2);
    std::vector <mu::script::runtime::expression *> expressions;
	mu::script::parser::topology topology (&root,
                                           [&expressions]
                                           (mu::script::runtime::expression * expression_a)
                                           {
                                               expressions.push_back (expression_a);
                                           },
                                           errors);
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (expressions.size () == 3);
    EXPECT_TRUE (expressions [0] == &e2);
    EXPECT_TRUE (expressions [1] == &e1);
    EXPECT_TRUE (expressions [2] == &root);
}

// Cycle
TEST (script_test, topology4)
{
    mu::core::errors::error_list errors;
	mu::script::runtime::expression root;
    mu::script::runtime::expression e1;
    mu::script::runtime::expression e2;
    root.dependencies.push_back (&e1);
    e2.dependencies.push_back (&e1);
    e1.dependencies.push_back (&e2);
    std::vector <mu::script::runtime::expression *> expressions;
	mu::script::parser::topology topology (&root,
                                           [&expressions]
                                           (mu::script::runtime::expression * expression_a)
                                           {
                                               expressions.push_back (expression_a);
                                           },
                                           errors);
    EXPECT_TRUE (errors ());
}

// Selection reference
TEST (script_test, topology5)
{
    mu::core::errors::error_list errors;
	mu::script::runtime::expression root;
    mu::script::runtime::expression e1;
    mu::script::runtime::selection s1 (&e1, 0);
    root.dependencies.push_back (&s1);
    std::vector <mu::script::runtime::expression *> expressions;
	mu::script::parser::topology topology (&root,
                                           [&expressions]
                                           (mu::script::runtime::expression * expression_a)
                                           {
                                               expressions.push_back (expression_a);
                                           },
                                           errors);
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (expressions.size () == 2);
    EXPECT_TRUE (expressions [0] == &e1);
    EXPECT_TRUE (expressions [1] == &root);
}
