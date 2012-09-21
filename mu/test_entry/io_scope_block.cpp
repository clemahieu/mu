#include <gtest/gtest.h>

#include <mu/core/node.h>
#include <mu/core/node_list.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/analyzer_extensions.h>
#include <mu/io/scope_global.h>
#include <mu/io/scope_block.h>
#include <mu/io/context.h>

//Block construction
TEST (io_test, scope_block1)
{
    mu::io::analyzer::extensions extensions;
    mu::io::scope::global global (extensions);
    mu::io::scope::block block (global);
}

// Reserve function
TEST (io_test, scope_block2)
{
    mu::io::analyzer::extensions extensions;
    mu::core::errors::error_list errors;
    mu::io::scope::global global (extensions);
    mu::io::scope::block block (global);
    auto result1 (block.reserve (errors, mu::string (U"test")));
    EXPECT_TRUE (!result1);
    mu::core::node node1;
    block.mapping [mu::string (U"test")] = &node1;
    auto result2 (block.reserve (errors, mu::string (U"test")));
    EXPECT_TRUE (result2);
    mu::io::context context;
    auto result3 (block.declare (errors, mu::string (U"test"), &node1, context));
    EXPECT_TRUE (result3);
    auto result4 (global.reserve (errors, mu::string (U"test")));
    EXPECT_TRUE (result4);
}

// Declare function
TEST (io_test, scope_block3)
{
    mu::io::analyzer::extensions extensions;
    mu::core::errors::error_list errors;
    mu::io::scope::global global (extensions);
    mu::io::scope::block block (global);
    mu::core::node node1;
    mu::io::context context;
    auto result1 (block.declare (errors, mu::string (U"test"), &node1, context));
    EXPECT_TRUE (!result1);
    auto result2 (block.declare (errors, mu::string (U"test"), &node1, context));
    EXPECT_TRUE (result2);
    auto result3 (block.reserve (errors, mu::string (U"test")));
    EXPECT_TRUE (result3);
}

// Pass function
TEST (io_test, scope_block4)
{
    mu::io::analyzer::extensions extensions;
    mu::io::scope::global global (extensions);
    mu::io::scope::block block (global);
    mu::core::errors::error_list errors;
    EXPECT_TRUE (block.unresolved.empty ());
    mu::multimap <mu::string, mu::core::node_list *> unresolved;
    mu::core::node_list nodes;
    unresolved.insert (decltype (unresolved)::value_type (mu::string (U"test"), &nodes));
    block.pass (unresolved);
    EXPECT_TRUE (!block.unresolved.empty ());
}

// End function
TEST (io_test, scope_block5)
{
    mu::io::analyzer::extensions extensions;
    mu::io::scope::global global (extensions);
    mu::io::scope::block block (global);
    mu::core::errors::error_list errors;
    EXPECT_TRUE (global.unresolved.empty ());
    EXPECT_TRUE (block.unresolved.empty ());
    mu::core::node_list nodes;
    block.unresolved.insert (decltype (block.unresolved)::value_type (mu::string (U"test"), &nodes));
    block.end ();
    EXPECT_TRUE (!global.unresolved.empty ());
}