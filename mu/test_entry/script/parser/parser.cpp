#include <gtest/gtest.h>

#include <mu/core/errors/error_list.h>
#include <mu/script/parser/parser.h>
#include <mu/io/tokens/stream_end.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/left_square.h>
#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/right_square.h>
#include <mu/script/cluster/node.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/runtime/expression.h>
#include <mu/script/runtime/reference.h>
#include <mu/script/runtime/selection.h>

#include <gc_cpp.h>

// Construction
TEST (script_test, parser1)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    EXPECT_TRUE (!errors ());
    EXPECT_TRUE (clusters.size () == 0);
}

// Empty program
TEST (script_test, parser2)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::stream_end, mu::io::debugging::context ());
    EXPECT_TRUE (!errors ());
    EXPECT_TRUE (clusters.size () == 1);
}

// Multiple clusters
TEST (script_test, parser3)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::stream_end, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::stream_end, mu::io::debugging::context ());
    EXPECT_TRUE (!errors ());
    EXPECT_TRUE (clusters.size () == 2);
}

// Invalid token in cluster
TEST (script_test, parser4)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    EXPECT_TRUE (errors ());
}

// Invalid routine name
TEST (script_test, parser5)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    EXPECT_TRUE (errors ());
}

// Valid routine name
TEST (script_test, parser6)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    EXPECT_TRUE (!errors ());
}

// Invalid parameters
TEST (script_test, parser7)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"u")), mu::io::debugging::context ());
    EXPECT_TRUE (errors ());
}

// Valid omitted parameters
TEST (script_test, parser8)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    EXPECT_TRUE (!errors ());
}

// Valid empty parameters
TEST (script_test, parser9)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    EXPECT_TRUE (!errors ());
}

// Invalid parameter name
TEST (script_test, parser10)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    EXPECT_TRUE (errors ());
}

// Valid parameter name
TEST (script_test, parser11)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"u")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    EXPECT_TRUE (!errors ());
}

// Invalid body
TEST (script_test, parser12)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    EXPECT_TRUE (errors ());
}

// Valid body
TEST (script_test, parser13)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    EXPECT_TRUE (!errors ());
}

// Invalid after body
TEST (script_test, parser14)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    EXPECT_TRUE (errors ());
}

// Valid cluster
TEST (script_test, parser15)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::stream_end, mu::io::debugging::context ());
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    ASSERT_TRUE (clusters [0]->routines.size () == 1);
    EXPECT_TRUE (clusters [0]->routines [0]->expressions.size () == 1);
}

// Valid routine with identifier
TEST (script_test, parser16)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::stream_end, mu::io::debugging::context ());
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    ASSERT_TRUE (clusters [0]->routines.size () == 1);
    EXPECT_TRUE (clusters [0]->routines [0]->expressions.size () == 1);
    EXPECT_TRUE (clusters [0]->routines [0]->expressions [0]->dependencies.size () == 1);
}

// Valid routine with expression in body
TEST (script_test, parser17)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::stream_end, mu::io::debugging::context ());
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    ASSERT_TRUE (clusters [0]->routines.size () == 1);
    ASSERT_TRUE (clusters [0]->routines [0]->expressions.size () == 2);
    EXPECT_TRUE (clusters [0]->routines [0]->expressions [0]->dependencies.size () == 0);
    ASSERT_TRUE (clusters [0]->routines [0]->expressions [1]->dependencies.size () == 1);
    ASSERT_TRUE (dynamic_cast <mu::script::runtime::reference *> (clusters [0]->routines [0]->expressions [1]->dependencies [0]) != nullptr);
    EXPECT_TRUE (static_cast <mu::script::runtime::reference *> (clusters [0]->routines [0]->expressions [1]->dependencies [0])->expression == clusters [0]->routines [0]->expressions [0]);
}

// Valid routine with expression in expression
TEST (script_test, parser18)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::stream_end, mu::io::debugging::context ());
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    ASSERT_TRUE (clusters [0]->routines.size () == 1);
    ASSERT_TRUE (clusters [0]->routines [0]->expressions.size () == 3);
    EXPECT_TRUE (clusters [0]->routines [0]->expressions [0]->dependencies.size () == 0);
    ASSERT_TRUE (clusters [0]->routines [0]->expressions [1]->dependencies.size () == 1);
    ASSERT_TRUE (dynamic_cast <mu::script::runtime::reference *> (clusters [0]->routines [0]->expressions [1]->dependencies [0]) != nullptr);
    EXPECT_TRUE (static_cast <mu::script::runtime::reference *> (clusters [0]->routines [0]->expressions [1]->dependencies [0])->expression == clusters [0]->routines [0]->expressions [0]);
    ASSERT_TRUE (clusters [0]->routines [0]->expressions [2]->dependencies.size () == 1);
    ASSERT_TRUE (dynamic_cast <mu::script::runtime::reference *> (clusters [0]->routines [0]->expressions [2]->dependencies [0]) != nullptr);
    EXPECT_TRUE (static_cast <mu::script::runtime::reference *> (clusters [0]->routines [0]->expressions [2]->dependencies [0])->expression == clusters [0]->routines [0]->expressions [1]);
}

// Invalid expression, missing name
TEST (script_test, parser19)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::stream_end, mu::io::debugging::context ());
    EXPECT_TRUE (errors ());
}

// Valid unreferenced expression because of naming
TEST (script_test, parser20)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"u")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::stream_end, mu::io::debugging::context ());
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    ASSERT_TRUE (clusters [0]->routines.size () == 1);
    ASSERT_TRUE (clusters [0]->routines [0]->expressions.size () == 1);
    EXPECT_TRUE (clusters [0]->routines [0]->expressions [0]->dependencies.size () == 0);
}

// Expression with name reference
TEST (script_test, parser21)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"u")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"u")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::stream_end, mu::io::debugging::context ());
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    ASSERT_TRUE (clusters [0]->routines.size () == 1);
    ASSERT_TRUE (clusters [0]->routines [0]->expressions.size () == 2);
    EXPECT_TRUE (clusters [0]->routines [0]->expressions [0]->dependencies.size () == 0);
    EXPECT_TRUE (clusters [0]->routines [0]->expressions [1]->dependencies.size () == 1);
    ASSERT_TRUE (dynamic_cast <mu::script::runtime::reference *> (clusters [0]->routines [0]->expressions [1]->dependencies [0]) != nullptr);
    EXPECT_TRUE (static_cast <mu::script::runtime::reference *> (clusters [0]->routines [0]->expressions [1]->dependencies [0])->expression == clusters [0]->routines [0]->expressions [0]);
}

// Expression with elements reference
TEST (script_test, parser22)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"u")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"u")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::stream_end, mu::io::debugging::context ());
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    ASSERT_TRUE (clusters [0]->routines.size () == 1);
    ASSERT_TRUE (clusters [0]->routines [0]->expressions.size () == 2);
    EXPECT_TRUE (clusters [0]->routines [0]->expressions [0]->dependencies.size () == 0);
    EXPECT_TRUE (clusters [0]->routines [0]->expressions [1]->dependencies.size () == 1);
    ASSERT_TRUE (dynamic_cast <mu::script::runtime::selection *> (clusters [0]->routines [0]->expressions [1]->dependencies [0]) != nullptr);
    EXPECT_TRUE (static_cast <mu::script::runtime::selection *> (clusters [0]->routines [0]->expressions [1]->dependencies [0])->expression == clusters [0]->routines [0]->expressions [0]);
}

// Reference to a parameter
TEST (script_test, parser23)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"u")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"u")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::stream_end, mu::io::debugging::context ());
    EXPECT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    ASSERT_TRUE (clusters [0]->routines.size () == 1);
    ASSERT_TRUE (clusters [0]->routines [0]->expressions.size () == 1);
    EXPECT_TRUE (clusters [0]->routines [0]->expressions [0]->dependencies.size () == 1);
}

// Missing body
TEST (script_test, parser24)
{
    mu::core::errors::error_list errors;
    std::vector <mu::script::cluster::node *> clusters;
    mu::script::parser::parser parser (errors, [&clusters] (mu::script::cluster::node * node_a) {clusters.push_back (node_a);});
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::stream_end, mu::io::debugging::context ());
    EXPECT_TRUE (errors ());
}