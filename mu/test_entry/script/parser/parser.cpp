#include <gtest/gtest.h>

#include <mu/core/errors/error_list.h>
#include <mu/script/parser/parser.h>
#include <mu/io/tokens/stream_end.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/left_square.h>

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