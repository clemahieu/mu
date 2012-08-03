#include <mu/io/analyzer/name_map.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/debugging/context.h>
#include <mu/core/node.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (io_test, name_map1)
{
    mu::io::analyzer::name_map map;
}

TEST (io_test, name_map2)
{
    mu::io::analyzer::name_map map;
    map.free_locals ();
}

// Test that unknown references reserve a spot in the expression
TEST (io_test, name_map3)
{
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    std::vector <mu::core::node *> nodes (1);
    map.fill_reference (mu::string (U"thing"), context, [&nodes] (mu::core::node * node_a) {nodes [0] = node_a;});
    ASSERT_TRUE (nodes.size () == 1);
    EXPECT_TRUE (nodes [0] == nullptr);
}

// Check that unknown references can be filled by globals
TEST (io_test, name_map4)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    std::vector <mu::core::node *> nodes (1);
    map.fill_reference (mu::string (U"thing"), context, [&nodes] (mu::core::node * node_a) {nodes [0] = node_a;});
    mu::core::node node;
    map.insert_global (errors, mu::string (U"thing"), &node, context);
    EXPECT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (nodes.size () == 1);
    EXPECT_TRUE (nodes [0] == &node);
}

// Check that unknown references can be filled by locals
TEST (io_test, name_map5)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    std::vector <mu::core::node *> nodes (1);
    map.fill_reference (mu::string (U"thing"), context, [&nodes] (mu::core::node * node_a) {nodes [0] = node_a;});
    mu::core::node node;
    map.insert_local (errors, mu::string (U"thing"), &node, context);
    EXPECT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (nodes.size () == 1);
    EXPECT_TRUE (nodes [0] == &node);
}

// Check that two different globals can be inserted
TEST (io_test, name_map6)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::node node;
    map.insert_local (errors, mu::string (U"thing"), &node, context);
    mu::core::node node2;
    map.insert_local (errors, mu::string (U"thing2"), &node2, context);
    EXPECT_TRUE (errors.errors.empty ());
}

// Check that two globals with the same name can't be inserted
TEST (io_test, name_map7)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::node node;
    map.insert_local (errors, mu::string (U"thing"), &node, context);
    mu::core::node node2;
    map.insert_local (errors, mu::string (U"thing"), &node2, context);
    EXPECT_TRUE (!errors.errors.empty ());
}

// Check that two different locals can be inserted
TEST (io_test, name_map8)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::node node;
    map.insert_local (errors, mu::string (U"thing"), &node, context);
    mu::core::node node2;
    map.insert_local (errors, mu::string (U"thing2"), &node2, context);
    EXPECT_TRUE (errors.errors.empty ());
}

// Check that two locals with the same name can't be inserted
TEST (io_test, name_map9)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::node node;
    map.insert_local (errors, mu::string (U"thing"), &node, context);
    mu::core::node node2;
    map.insert_local (errors, mu::string (U"thing"), &node2, context);
    EXPECT_TRUE (!errors.errors.empty ());
}

// Check that a local name can be reused after clearing them
TEST (io_test, name_map10)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::node node;
    map.insert_local (errors, mu::string (U"thing"), &node, context);
    map.free_locals ();
    mu::core::node node2;
    map.insert_local (errors, mu::string (U"thing"), &node2, context);
    EXPECT_TRUE (errors.errors.empty ());
}

// Check that a local name can't collide with an existing global name
TEST (io_test, name_map11)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::node node;
    map.insert_global (errors, mu::string (U"thing"), &node, context);
    mu::core::node node2;
    map.insert_local (errors, mu::string (U"thing"), &node2, context);
    EXPECT_TRUE (!errors.errors.empty ());
}

// Check that a global name can't collide with an existing local name in local scope
TEST (io_test, name_map12)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::node node;
    map.insert_local (errors, mu::string (U"thing"), &node, context);
    mu::core::node node2;
    map.insert_global (errors, mu::string (U"thing"), &node2, context);
    EXPECT_TRUE (!errors.errors.empty ());
}

// Check that a global name can't collide with an existing local name out of local scope
TEST (io_test, name_map13)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::node node;
    map.insert_local (errors, mu::string (U"thing"), &node, context);
    map.free_locals ();
    mu::core::node node2;
    map.insert_global (errors, mu::string (U"thing"), &node2, context);
    EXPECT_TRUE (!errors.errors.empty ());
}

// Check that multiple references can be resolved
TEST (io_test, name_map14)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    std::vector <mu::core::node *> nodes (2);
    mu::core::node node;
    map.fill_reference (mu::string (U"thing"), context, [&nodes] (mu::core::node * node_a) {nodes [0] = node_a;});
    map.fill_reference (mu::string (U"thing"), context, [&nodes] (mu::core::node * node_a) {nodes [1] = node_a;});
    map.insert_global (errors, mu::string (U"thing"), &node, context);
    EXPECT_TRUE (errors.errors.empty ());
    EXPECT_TRUE (nodes.size () == 2);
    EXPECT_TRUE (nodes [0] == &node);
    EXPECT_TRUE (nodes [1] == &node);
}

// Check that there are no errors when there are no names
TEST (io_test, name_map15)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::core::node node;
    map.finalize (errors);
    EXPECT_TRUE (errors.errors.empty ());
}

// Check that there are no errors when everything is resolved
TEST (io_test, name_map16)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::node node;
    std::vector <mu::core::node *> nodes (1);
    map.insert_global (errors, mu::string (U"thing"), &node, context);
    map.fill_reference (mu::string (U"thing"), context, [&nodes] (mu::core::node * node_a) {nodes [0] = node_a;});
    map.finalize (errors);
    EXPECT_TRUE (errors.errors.empty ());
}

// Check that there are errors when there are unresolved references
TEST (io_test, name_map17)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::node node;
    std::vector <mu::core::node *> nodes (1);
    map.fill_reference (mu::string (U"thing"), context, [&nodes] (mu::core::node * node_a) {nodes [0] = node_a;});
    map.finalize (errors);
    EXPECT_TRUE (!errors.errors.empty ());
}

// Check that a local declaration can't resolve references in other functions
TEST (io_test, name_map18)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::node node;
    std::vector <mu::core::node *> nodes (1);
    map.fill_reference (mu::string (U"thing"), context, [&nodes] (mu::core::node * node_a) {nodes [0] = node_a;});
    map.free_locals ();
    map.insert_local (errors, mu::string (U"thing"), &node, context);
    EXPECT_TRUE (!errors.errors.empty ());
}