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

// Refer function unresolved
TEST (io_test, scope_block6)
{
    mu::io::analyzer::extensions extensions;
    mu::io::scope::global global (extensions);
    mu::io::scope::block block (global);
    mu::core::errors::error_list errors;
    EXPECT_TRUE (global.unresolved.empty ());
    EXPECT_TRUE (block.unresolved.empty ());
    mu::io::context context;
    mu::core::node_list nodes;
    block.refer (mu::string (U"test"), context, nodes);
    EXPECT_TRUE (global.unresolved.empty ());
    EXPECT_TRUE (block.unresolved.find (mu::string (U"test")) != block.unresolved.end ());
    block.end ();
    EXPECT_TRUE (global.unresolved.find (mu::string (U"test")) != global.unresolved.end ());
    auto failed (global.end (errors));
    EXPECT_TRUE (failed);
    EXPECT_TRUE (!errors.errors.empty ());
}

// Refer function unresolved
TEST (io_test, scope_block7)
{
    mu::io::analyzer::extensions extensions;
    mu::io::scope::global global (extensions);
    mu::io::scope::block block (global);
    mu::core::errors::error_list errors;
    EXPECT_TRUE (global.unresolved.empty ());
    EXPECT_TRUE (block.unresolved.empty ());
    mu::io::context context;
    mu::core::node_list nodes;
    block.refer (mu::string (U"test"), context, nodes);
    EXPECT_TRUE (global.unresolved.empty ());
    EXPECT_TRUE (block.unresolved.find (mu::string (U"test")) != block.unresolved.end ());
    block.end ();
    EXPECT_TRUE (global.unresolved.find (mu::string (U"test")) != global.unresolved.end ());
    mu::core::node node1;
    auto result1 (global.declare(errors, mu::string (U"test"), &node1, context));
    EXPECT_TRUE (!result1);
    EXPECT_TRUE (global.unresolved.empty ());
}

// Refer function unresolved
TEST (io_test, scope_block8)
{
    mu::io::analyzer::extensions extensions;
    mu::io::scope::global global (extensions);
    mu::io::scope::block block (global);
    mu::core::errors::error_list errors;
    EXPECT_TRUE (global.unresolved.empty ());
    EXPECT_TRUE (block.unresolved.empty ());
    mu::io::context context;
    mu::core::node_list nodes;
    block.refer (mu::string (U"test"), context, nodes);
    EXPECT_TRUE (global.unresolved.empty ());
    EXPECT_TRUE (block.unresolved.find (mu::string (U"test")) != block.unresolved.end ());
    mu::core::node node1;
    auto result1 (block.declare(errors, mu::string (U"test"), &node1, context));
    EXPECT_TRUE (block.unresolved.find (mu::string (U"test")) == block.unresolved.end ());
    ASSERT_TRUE (nodes.nodes.size () == 1);
    auto nodes1 (dynamic_cast <mu::core::node_list *> (nodes.nodes [0]));
    ASSERT_TRUE (nodes1 != nullptr);
    ASSERT_TRUE (nodes1->size () == 1);
    EXPECT_TRUE (nodes1->nodes [0] == &node1);
}

// Reference can't be resolved by non-dominating scope
TEST (io_test, scope_block9)
{
    mu::io::analyzer::extensions extensions;
    mu::io::scope::global global (extensions);
    mu::io::scope::block block (global);
    mu::core::errors::error_list errors;
    EXPECT_TRUE (global.unresolved.empty ());
    EXPECT_TRUE (block.unresolved.empty ());
    mu::io::context context;
    mu::core::node_list nodes;
    block.refer (mu::string (U"test"), context, nodes);
    EXPECT_TRUE (global.unresolved.empty ());
    EXPECT_TRUE (block.unresolved.find (mu::string (U"test")) != block.unresolved.end ());
    block.end ();
    EXPECT_TRUE (global.unresolved.find (mu::string (U"test")) != global.unresolved.end ());
    mu::io::scope::block block2 (global);
    mu::core::node node1;
    auto result1 (block2.declare (errors, mu::string (U"test"), &node1, context));
    EXPECT_TRUE (result1);
}

// Declare same name different blocks
TEST (io_test, scope_block10)
{
    mu::io::analyzer::extensions extensions;
    mu::core::errors::error_list errors;
    mu::io::scope::global global (extensions);
    mu::io::scope::block block (global);
    mu::core::node node1;
    mu::io::context context;
    auto result1 (block.declare (errors, mu::string (U"test"), &node1, context));
    EXPECT_TRUE (!result1);
    mu::io::scope::block block1 (global);
    auto result2 (block.declare (errors, mu::string (U"test"), &node1, context));
    EXPECT_TRUE (!result2);
}