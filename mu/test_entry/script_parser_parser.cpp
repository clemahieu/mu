#include <gtest/gtest.h>

#include <mu/io/tokens_implementor.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/parser_parser.h>
#include <mu/script/ast_cluster.h>
#include <mu/script/ast_routine.h>
#include <mu/script/ast_definite_expression.h>
#include <mu/script/ast_reference.h>
#include <mu/script/parser_scope_node.h>
#include <mu/script/tokens_keyword_if.h>
#include <mu/script/ast_if_expression.h>

#include <gc_cpp.h>

// Construction
TEST (script_test, parser1)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    EXPECT_TRUE (!errors ());
    EXPECT_TRUE (clusters.size () == 0);
}

// Empty program
TEST (script_test, parser2)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::stream_end (context));
    EXPECT_TRUE (!errors ());
    EXPECT_TRUE (clusters.size () == 1);
}

// Multiple clusters
TEST (script_test, parser3)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::stream_end (context));
    parser (mu::io::tokens::stream_end (context));
    EXPECT_TRUE (!errors ());
    EXPECT_TRUE (clusters.size () == 2);
}

// Invalid token in cluster
TEST (script_test, parser4)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::divider (context));
    EXPECT_TRUE (errors ());
}

// Invalid routine name
TEST (script_test, parser5)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::divider (context));
    EXPECT_TRUE (errors ());
}

// Valid routine name
TEST (script_test, parser6)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    EXPECT_TRUE (!errors ());
}

// Invalid parameters
TEST (script_test, parser7)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::identifier (context, mu::string (U"u")));
    EXPECT_TRUE (errors ());
}

// Valid omitted parameters
TEST (script_test, parser8)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    EXPECT_TRUE (!errors ());
}

// Valid empty parameters
TEST (script_test, parser9)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::right_square (context));
    EXPECT_TRUE (!errors ());
}

// Invalid parameter name
TEST (script_test, parser10)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::right_square (context));
    EXPECT_TRUE (errors ());
}

// Valid parameter name
TEST (script_test, parser11)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"u")));
    parser (mu::io::tokens::right_square (context));
    EXPECT_TRUE (!errors ());
}

// Invalid body
TEST (script_test, parser12)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::divider (context));
    EXPECT_TRUE (errors ());
}

// Valid body
TEST (script_test, parser13)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::right_square (context));
    EXPECT_TRUE (!errors ());
}

// Invalid after body
TEST (script_test, parser14)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::divider (context));
    EXPECT_TRUE (errors ());
}

// Valid cluster
TEST (script_test, parser15)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    ASSERT_TRUE (clusters [0]->routines.size () == 1);
    EXPECT_TRUE (clusters [0]->routines [0]->body->nodes.size () == 0);
}

// Valid routine with identifier
TEST (script_test, parser16)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    ASSERT_TRUE (clusters [0]->routines.size () == 1);
    EXPECT_TRUE (clusters [0]->routines [0]->body->nodes.size () == 1);
}

// Valid routine with expression in body
TEST (script_test, parser17)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    ASSERT_TRUE (clusters [0]->routines.size () == 1);
    ASSERT_TRUE (clusters [0]->routines [0]->body->nodes.size () == 1);
    auto i (clusters [0]->routines [0]->body->nodes.begin ());
    ASSERT_TRUE (dynamic_cast <mu::script::ast::definite_expression *> (*i) != nullptr);
    auto expression2 (static_cast <mu::script::ast::definite_expression *> (*i));
    ASSERT_TRUE (expression2->nodes.size () == 0);
}

// Valid routine with expression in expression
TEST (script_test, parser18)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    ASSERT_TRUE (clusters [0]->routines.size () == 1);
    ASSERT_TRUE (clusters [0]->routines [0]->body->nodes.size () == 1);
    auto i (clusters [0]->routines [0]->body->nodes.begin ());
    ASSERT_TRUE (i != clusters [0]->routines [0]->body->nodes.end ());
    ASSERT_TRUE (dynamic_cast <mu::script::ast::definite_expression *> (*i) != nullptr);
    auto expression2 (static_cast <mu::script::ast::definite_expression *> (*i));
    ASSERT_TRUE (expression2->nodes.size () == 1);
    auto j (expression2->nodes.begin ());
    ASSERT_TRUE (j != expression2->nodes.end ());
    auto expression3 (static_cast <mu::script::ast::definite_expression *> (*j));
    EXPECT_TRUE (expression3->nodes.size () == 0);
}

// Invalid expression, missing name
TEST (script_test, parser19)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    EXPECT_TRUE (errors ());
}

// Expression with name reference
TEST (script_test, parser21)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"u")));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"u")));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    ASSERT_TRUE (clusters [0]->routines.size () == 1);
    ASSERT_TRUE (clusters [0]->routines [0]->body->nodes.size () == 2);
    auto i (clusters [0]->routines [0]->body->nodes.begin ());
    ASSERT_TRUE (i != clusters [0]->routines [0]->body->nodes.end ());
    ASSERT_TRUE (dynamic_cast <mu::script::ast::definite_expression *> (*i) != nullptr);
    auto expression2 (static_cast <mu::script::ast::definite_expression *> (*i));
    ASSERT_TRUE (expression2->nodes.size () == 0);
    ++i;
    ASSERT_TRUE (i != clusters [0]->routines [0]->body->nodes.end ());
    ASSERT_TRUE (dynamic_cast <mu::script::ast::definite_expression *> (*i) != nullptr);
    auto expression3 (static_cast <mu::script::ast::definite_expression *> (*i));
    ASSERT_TRUE (expression3 == expression2);
}

// Expression with elements reference
TEST (script_test, parser22)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"u")));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"u")));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    ASSERT_TRUE (clusters [0]->routines.size () == 1);
    ASSERT_TRUE (clusters [0]->routines [0]->body->nodes.size () == 2);
    auto i (clusters [0]->routines [0]->body->nodes.begin ());
    ASSERT_TRUE (i != clusters [0]->routines [0]->body->nodes.end ());
    ASSERT_TRUE (dynamic_cast <mu::script::ast::reference *> (*i) != nullptr);
    auto reference1 (static_cast <mu::script::ast::reference *> (*i));
    auto expression2 (dynamic_cast<mu::script::ast::definite_expression *>(reference1->expression));
    ASSERT_TRUE (expression2 != nullptr);
    EXPECT_TRUE (expression2->nodes.size () == 0);
    EXPECT_TRUE (reference1->position == 0);
    ++i;
    ASSERT_TRUE (i != clusters [0]->routines [0]->body->nodes.end ());
    ASSERT_TRUE (dynamic_cast <mu::script::ast::expression *> (*i) != nullptr);
    auto expression1 (static_cast <mu::script::ast::expression *> (*i));
    EXPECT_TRUE (expression1 == reference1->expression);
}

// Reference to a parameter
TEST (script_test, parser23)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"u")));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"u")));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    ASSERT_TRUE (clusters [0]->routines.size () == 1);
    ASSERT_TRUE (clusters [0]->routines [0]->body->nodes.size () == 1);
}

// Missing body
TEST (script_test, parser24)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    EXPECT_TRUE (errors ());
}

// Unresolved reference body
TEST (script_test, parser25)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"u")));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    EXPECT_TRUE (errors ());
}

// Mutually referential functions
TEST (script_test, parser26)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"u")));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"u")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster1 (clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 2);
    auto routine1 (cluster1->routines [0]);
    auto routine2 (cluster1->routines [1]);
    ASSERT_TRUE (routine1->body->nodes.nodes.size () == 1);
    auto i (routine1->body->nodes.begin ());
    ASSERT_TRUE (i != routine1->body->nodes.end ());
    auto d1 (*i);
    ASSERT_TRUE (d1 == routine2);
    ASSERT_TRUE (routine2->body->nodes.nodes.size () == 1);
    auto j (routine2->body->nodes.begin ());
    ASSERT_TRUE (j != routine2->body->nodes.end ());
    auto d2 (*j);
    ASSERT_TRUE (d2 = routine1);
}

// Check that injected nodes can be used
TEST (script_test, parser27)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    auto node1 (new (GC) mu::core::node);
    injected.injected [mu::string (U"u")] = node1;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"u")));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster1 (clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    auto expression1 (cluster1->routines [0]->body);
    ASSERT_TRUE (expression1->nodes.size () == 1);
    auto node2 (*expression1->nodes.begin());
    ASSERT_TRUE (node1 == node2);
}

// Error invalid if beginning
TEST (script_test, parser28)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::value (context, new (GC) mu::script::tokens::keyword_if));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    ASSERT_TRUE (errors ());
}

// Empty if
TEST (script_test, parser29)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::value (context, new (GC) mu::script::tokens::keyword_if));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster1 (clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    auto expression1 (cluster1->routines [0]->body);
    ASSERT_TRUE (expression1->nodes.size () == 1);
    auto node2 (dynamic_cast <mu::script::ast::if_expression *> (*expression1->nodes.begin ()));
    ASSERT_TRUE (node2 != nullptr);
    ASSERT_TRUE (node2->predicate->nodes.size () == 0);
    ASSERT_TRUE (node2->true_branch->nodes.size () == 0);
    ASSERT_TRUE (node2->false_branch->nodes.size () == 0);
}

// Predicate node
TEST (script_test, parser30)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::value (context, new (GC) mu::script::tokens::keyword_if));
    parser (mu::io::tokens::left_square (context));
    auto node1 (new (GC) mu::core::node);
    parser (mu::io::tokens::value (context, node1));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster1 (clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    auto expression1 (cluster1->routines [0]->body);
    ASSERT_TRUE (expression1->nodes.size () == 1);
    auto node2 (dynamic_cast <mu::script::ast::if_expression *> (*expression1->nodes.begin ()));
    ASSERT_TRUE (node2 != nullptr);
    ASSERT_TRUE (node2->predicate->nodes.size () == 1);
    auto node3 (*node2->predicate->nodes.begin());
    ASSERT_TRUE (node1 == node3);
    ASSERT_TRUE (node2->true_branch->nodes.size () == 0);
    ASSERT_TRUE (node2->false_branch->nodes.size () == 0);
}

// True branch node
TEST (script_test, parser31)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::value (context, new (GC) mu::script::tokens::keyword_if));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::divider (context));
    auto node1 (new (GC) mu::core::node);
    parser (mu::io::tokens::value (context, node1));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster1 (clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    auto expression1 (cluster1->routines [0]->body);
    ASSERT_TRUE (expression1->nodes.size () == 1);
    auto node2 (dynamic_cast <mu::script::ast::if_expression *> (*expression1->nodes.begin ()));
    ASSERT_TRUE (node2 != nullptr);
    ASSERT_TRUE (node2->predicate->nodes.size () == 0);
    ASSERT_TRUE (node2->true_branch->nodes.size () == 1);
    auto node3 (*node2->true_branch->nodes.begin());
    ASSERT_TRUE (node1 == node3);
    ASSERT_TRUE (node2->false_branch->nodes.size () == 0);
}

// False branch node
TEST (script_test, parser32)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::value (context, new (GC) mu::script::tokens::keyword_if));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::divider (context));
    auto node1 (new (GC) mu::core::node);
    parser (mu::io::tokens::value (context, node1));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster1 (clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    auto expression1 (cluster1->routines [0]->body);
    ASSERT_TRUE (expression1->nodes.size () == 1);
    auto node2 (dynamic_cast <mu::script::ast::if_expression *> (*expression1->nodes.begin ()));
    ASSERT_TRUE (node2 != nullptr);
    ASSERT_TRUE (node2->predicate->nodes.size () == 0);
    ASSERT_TRUE (node2->true_branch->nodes.size () == 0);
    ASSERT_TRUE (node2->false_branch->nodes.size () == 1);
    auto node3 (*node2->false_branch->nodes.begin());
    ASSERT_TRUE (node1 == node3);
}

// Error name node
TEST (script_test, parser33)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::value (context, new (GC) mu::script::tokens::keyword_if));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::divider (context));
    auto node1 (new (GC) mu::core::node);
    parser (mu::io::tokens::value (context, node1));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    ASSERT_TRUE (errors ());
}

// Name node
TEST (script_test, parser34)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::value (context, new (GC) mu::script::tokens::keyword_if));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::divider (context));
    mu::io::tokens::identifier identifier1 (context, mu::string (U"u"));
    parser (identifier1);
    parser (mu::io::tokens::right_square (context));
    parser (identifier1);
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster1 (clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    auto expression1 (cluster1->routines [0]->body);
    ASSERT_TRUE (expression1->nodes.size () == 2);
    auto current (expression1->nodes.begin ());
    auto node2 (dynamic_cast <mu::script::ast::if_expression *> (*current));
    ASSERT_TRUE (node2 != nullptr);
    ASSERT_TRUE (node2->predicate->nodes.size () == 0);
    ASSERT_TRUE (node2->true_branch->nodes.size () == 0);
    ASSERT_TRUE (node2->false_branch->nodes.size () == 0);
    ++current;
    auto node3 (dynamic_cast <mu::script::ast::if_expression *> (*current));
    ASSERT_TRUE (node2 == node3);
}

// Element node
TEST (script_test, parser35)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::value (context, new (GC) mu::script::tokens::keyword_if));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::divider (context));
    mu::io::tokens::identifier identifier1 (context, mu::string (U"u"));
    mu::io::tokens::identifier identifier2 (context, mu::string (U"v"));
    parser (identifier1);
    parser (identifier2);
    parser (mu::io::tokens::right_square (context));
    parser (identifier1);
    parser (identifier2);
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster1 (clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    auto expression1 (cluster1->routines [0]->body);
    ASSERT_TRUE (expression1->nodes.size () == 3);
    auto current (expression1->nodes.begin ());
    auto node2 (dynamic_cast <mu::script::ast::if_expression *> (*current));
    ASSERT_TRUE (node2 != nullptr);
    ASSERT_TRUE (node2->predicate->nodes.size () == 0);
    ASSERT_TRUE (node2->true_branch->nodes.size () == 0);
    ASSERT_TRUE (node2->false_branch->nodes.size () == 0);
    ++current;
    auto node3 (dynamic_cast <mu::script::ast::reference *> (*current));
    ASSERT_TRUE (node3 != nullptr);
    ASSERT_TRUE (node3->expression == node2);
    ASSERT_TRUE (node3->position == 0);
    ++current;
    auto node4 (dynamic_cast <mu::script::ast::reference *> (*current));
    ASSERT_TRUE (node4 != nullptr);
    ASSERT_TRUE (node4->expression == node2);
    ASSERT_TRUE (node4->position == 1);
}

// Error element node
TEST (script_test, parser36)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::value (context, new (GC) mu::script::tokens::keyword_if));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::divider (context));
    auto node1 (new (GC) mu::core::node);
    parser (mu::io::tokens::value (context, node1));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    ASSERT_TRUE (errors ());
}

// Predicate expression
TEST (script_test, parser37)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::value (context, new (GC) mu::script::tokens::keyword_if));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster1 (clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    auto expression1 (cluster1->routines [0]->body);
    ASSERT_TRUE (expression1->nodes.size () == 1);
    auto current (expression1->nodes.begin ());
    auto node2 (dynamic_cast <mu::script::ast::if_expression *> (*current));
    ASSERT_TRUE (node2 != nullptr);
    ASSERT_TRUE (node2->predicate->nodes.size () == 1);
    ASSERT_TRUE (node2->true_branch->nodes.size () == 0);
    ASSERT_TRUE (node2->false_branch->nodes.size () == 0);
    auto expression2 (dynamic_cast <mu::script::ast::definite_expression *> (*node2->predicate->nodes.begin()));
    ASSERT_TRUE (expression2 != nullptr);
    ASSERT_TRUE (expression2->nodes.size () == 0);
}

// True branch expression
TEST (script_test, parser38)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::value (context, new (GC) mu::script::tokens::keyword_if));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster1 (clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    auto expression1 (cluster1->routines [0]->body);
    ASSERT_TRUE (expression1->nodes.size () == 1);
    auto current (expression1->nodes.begin ());
    auto node2 (dynamic_cast <mu::script::ast::if_expression *> (*current));
    ASSERT_TRUE (node2 != nullptr);
    ASSERT_TRUE (node2->predicate->nodes.size () == 0);
    ASSERT_TRUE (node2->true_branch->nodes.size () == 1);
    ASSERT_TRUE (node2->false_branch->nodes.size () == 0);
    auto expression2 (dynamic_cast <mu::script::ast::definite_expression *> (*node2->true_branch->nodes.begin()));
    ASSERT_TRUE (expression2 != nullptr);
    ASSERT_TRUE (expression2->nodes.size () == 0);
}

// False branch expression
TEST (script_test, parser39)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::value (context, new (GC) mu::script::tokens::keyword_if));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster1 (clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    auto expression1 (cluster1->routines [0]->body);
    ASSERT_TRUE (expression1->nodes.size () == 1);
    auto current (expression1->nodes.begin ());
    auto node2 (dynamic_cast <mu::script::ast::if_expression *> (*current));
    ASSERT_TRUE (node2 != nullptr);
    ASSERT_TRUE (node2->predicate->nodes.size () == 0);
    ASSERT_TRUE (node2->true_branch->nodes.size () == 0);
    ASSERT_TRUE (node2->false_branch->nodes.size () == 1);
    auto expression2 (dynamic_cast <mu::script::ast::definite_expression *> (*node2->false_branch->nodes.begin()));
    ASSERT_TRUE (expression2 != nullptr);
    ASSERT_TRUE (expression2->nodes.size () == 0);
}

// If inside expression
TEST (script_test, parser40)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::value (context, new (GC) mu::script::tokens::keyword_if));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster1 (clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    auto expression1 (cluster1->routines [0]->body);
    ASSERT_TRUE (expression1->nodes.size () == 1);
    auto current (expression1->nodes.begin ());
    auto node2 (dynamic_cast <mu::script::ast::definite_expression *> (*current));
    ASSERT_TRUE (node2 != nullptr);
    ASSERT_TRUE (node2->nodes.size () == 1);
    auto node3 (dynamic_cast <mu::script::ast::if_expression *> (*node2->nodes.begin()));
    ASSERT_TRUE (node3 != nullptr);
    ASSERT_TRUE (node3->predicate->nodes.size () == 0);
    ASSERT_TRUE (node3->true_branch->nodes.size () == 0);
    ASSERT_TRUE (node3->false_branch->nodes.size () == 0);
}

// Empty if after a node
TEST (script_test, parser41)
{
    mu::io::context context;
    mu::core::errors::error_list errors;
    std::vector <mu::script::ast::cluster *> clusters;
    mu::script::parser_scope::node injected;
    mu::script::parser::parser parser (errors,
                                       [&clusters]
                                       (mu::script::ast::cluster * node_a)
                                       {
                                           clusters.push_back (node_a);
                                       }, &injected);
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::identifier (context, mu::string (U"t")));
    parser (mu::io::tokens::divider (context));
    parser (mu::io::tokens::left_square (context));
    auto node1 (new (GC) mu::core::node);
    parser (mu::io::tokens::value (context, node1));
    parser (mu::io::tokens::value (context, new (GC) mu::script::tokens::keyword_if));
    parser (mu::io::tokens::left_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::right_square (context));
    parser (mu::io::tokens::stream_end (context));
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster1 (clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    auto expression1 (cluster1->routines [0]->body);
    ASSERT_TRUE (expression1->nodes.size () == 2);
    auto current (expression1->nodes.begin ());
    auto node3 (*current);
    ASSERT_TRUE (node3 == node1);
    ++current;
    auto node2 (dynamic_cast <mu::script::ast::if_expression *> (*current));
    ASSERT_TRUE (node2 != nullptr);
    ASSERT_TRUE (node2->predicate->nodes.size () == 0);
    ASSERT_TRUE (node2->true_branch->nodes.size () == 0);
    ASSERT_TRUE (node2->false_branch->nodes.size () == 0);
}
