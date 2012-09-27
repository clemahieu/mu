#include <gtest/gtest.h>

#include <mu/core/node_list.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/scope_global.h>
#include <mu/io/analyzer_extensions.h>
#include <mu/test_entry/io_extension5.h>
#include <mu/io/context.h>

TEST (io_test, scope_global1)
{
    mu::io::analyzer::extensions extensions;
    mu::io::scope::global global (extensions);
}

// End function
TEST (io_test, scope_global2)
{
    mu::io::analyzer::extensions extensions;
    mu::io::scope::global global (extensions);
    mu::core::errors::error_list errors;
    auto result1 (global.end (errors));
    EXPECT_TRUE (!result1);
    global.unresolved.insert (decltype(global.unresolved)::value_type (mu::string (U"test"), nullptr));
    auto result2 (global.end (errors));
    EXPECT_TRUE (result2);
}

// Pass function
TEST (io_test, scope_global3)
{
    mu::io::analyzer::extensions extensions;
    mu::io::scope::global global (extensions);
    mu::core::errors::error_list errors;
    EXPECT_TRUE (global.unresolved.empty ());
    mu::multimap <mu::string, mu::core::node_list *> unresolved;
    mu::core::node_list nodes;
    unresolved.insert (decltype (unresolved)::value_type (mu::string (U"test"), &nodes));
    global.pass (unresolved);
    EXPECT_TRUE (!global.unresolved.empty ());
}

// Reserve function
TEST (io_test, scope_global4)
{
    mu::io::analyzer::extensions extensions;
    mu::io::scope::global global (extensions);
    mu::core::errors::error_list errors;
    auto result1 (global.reserve (errors, mu::string (U"test")));
    EXPECT_TRUE (!result1);
    auto result2 (global.reserve (errors, mu::string (U"test")));
    EXPECT_TRUE (result2);
    auto fail (extensions.add <mu::io_test::extension5> (mu::string (U"ext")));
    ASSERT_TRUE (!fail);
    auto result3 (global.reserve (errors, mu::string (U"ext")));
    EXPECT_TRUE (result3);
    auto result4 (global.reserve (errors, mu::string (U"exta")));
    EXPECT_TRUE (result3);
    mu::core::node node1;
    mu::io::context context;
    auto result5 (global.declare (errors, mu::string (U"test"), &node1, context));
    EXPECT_TRUE (result5);
}

// Declare function
TEST (io_test, scope_global5)
{
    mu::io::analyzer::extensions extensions;
    mu::io::scope::global global (extensions);
    mu::core::errors::error_list errors;
    mu::core::node node1;
    mu::io::context context;
    auto result1 (global.declare (errors, mu::string (U"test"), &node1, context));
    EXPECT_TRUE (!result1);
    auto result2 (global.reserve (errors, mu::string (U"test")));
    EXPECT_TRUE (result2);
    auto result3 (global.declare (errors, mu::string (U"test"), &node1, context));
    EXPECT_TRUE (result3);
}

// Fill function
TEST (io_test, scope_global6)
{
    mu::io::analyzer::extensions extensions;
    mu::io::scope::global global (extensions);
    mu::core::errors::error_list errors;
    mu::core::node_list nodes;
    mu::io::context context;
    auto result1 (global.fill (mu::string (U"test"), nodes));
    EXPECT_TRUE (result1);
    mu::core::node node1;
    auto result2 (global.declare (errors, mu::string (U"test"), &node1, context));
    EXPECT_TRUE (!result2);
    auto result3 (global.fill (mu::string (U"test"), nodes));
    EXPECT_TRUE (!result3);
    EXPECT_TRUE (nodes.nodes.size () == 1);
    EXPECT_TRUE (nodes.nodes [0] == &node1);
}