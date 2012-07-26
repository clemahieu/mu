#include <mu/io/analyzer/name_map.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/debugging/context.h>
#include <mu/core/expression.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (io_test, name_map1)
{
    mu::io::analyzer::name_map map;
}

TEST (io_test, name_map2)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    map.free_locals (&errors);
    EXPECT_TRUE (errors.errors.empty ());
}

// Test that unknown references reserve a spot in the expression
TEST (io_test, name_map3)
{
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::expression expression;
    map.fill_reference (mu::string (U"thing"), context, expression);
    ASSERT_TRUE (expression.dependencies.size () == 1);
    EXPECT_TRUE (expression.dependencies [0] == nullptr);
}

// Check that unknown references can be filled by globals
TEST (io_test, name_map4)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::expression expression;
    map.fill_reference (mu::string (U"thing"), context, expression);
    mu::core::node node;
    map.insert_global(&errors, mu::string (U"thing"), &node);
    EXPECT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (expression.dependencies.size () == 1);
    EXPECT_TRUE (expression.dependencies [0] == &node);
}

// Check that unknown references can be filled by locals
TEST (io_test, name_map5)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::expression expression;
    map.fill_reference (mu::string (U"thing"), context, expression);
    mu::core::node node;
    map.insert_local (&errors, mu::string (U"thing"), &node);
    EXPECT_TRUE (errors.errors.empty ());
    ASSERT_TRUE (expression.dependencies.size () == 1);
    EXPECT_TRUE (expression.dependencies [0] == &node);
}

// Check that two different globals can be inserted
TEST (io_test, name_map6)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::expression expression;
    mu::core::node node;
    map.insert_local (&errors, mu::string (U"thing"), &node);
    mu::core::node node2;
    map.insert_local (&errors, mu::string (U"thing2"), &node2);
    EXPECT_TRUE (errors.errors.empty ());
}

// Check that two globals with the same name can't be inserted
TEST (io_test, name_map7)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::expression expression;
    mu::core::node node;
    map.insert_local (&errors, mu::string (U"thing"), &node);
    mu::core::node node2;
    map.insert_local (&errors, mu::string (U"thing"), &node2);
    EXPECT_TRUE (!errors.errors.empty ());
}

// Check that two different locals can be inserted
TEST (io_test, name_map8)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::expression expression;
    mu::core::node node;
    map.insert_local (&errors, mu::string (U"thing"), &node);
    mu::core::node node2;
    map.insert_local (&errors, mu::string (U"thing2"), &node2);
    EXPECT_TRUE (errors.errors.empty ());
}

// Check that two locals with the same name can't be inserted
TEST (io_test, name_map9)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::expression expression;
    mu::core::node node;
    map.insert_local (&errors, mu::string (U"thing"), &node);
    mu::core::node node2;
    map.insert_local (&errors, mu::string (U"thing"), &node2);
    EXPECT_TRUE (!errors.errors.empty ());
}

// Check that a local name can be reused after clearing them
TEST (io_test, name_map10)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::expression expression;
    mu::core::node node;
    map.insert_local (&errors, mu::string (U"thing"), &node);
    map.free_locals (&errors);
    mu::core::node node2;
    map.insert_local (&errors, mu::string (U"thing"), &node2);
    EXPECT_TRUE (errors.errors.empty ());
}

// Check that a local name can't collide with an existing global name
TEST (io_test, name_map11)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::expression expression;
    mu::core::node node;
    map.insert_global (&errors, mu::string (U"thing"), &node);
    mu::core::node node2;
    map.insert_local (&errors, mu::string (U"thing"), &node2);
    EXPECT_TRUE (!errors.errors.empty ());
}

// Check that a global name can't collide with an existing local name in local scope
TEST (io_test, name_map12)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::expression expression;
    mu::core::node node;
    map.insert_local (&errors, mu::string (U"thing"), &node);
    mu::core::node node2;
    map.insert_global (&errors, mu::string (U"thing"), &node2);
    EXPECT_TRUE (!errors.errors.empty ());
}

// Check that a global name can't collide with an existing local name out of local scope
TEST (io_test, name_map13)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::expression expression;
    mu::core::node node;
    map.insert_local (&errors, mu::string (U"thing"), &node);
    map.free_locals (&errors);
    mu::core::node node2;
    map.insert_global (&errors, mu::string (U"thing"), &node2);
    EXPECT_TRUE (!errors.errors.empty ());
}

// Check that multiple references can be resolved
TEST (io_test, name_map14)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::expression expression;
    mu::core::node node;
    map.fill_reference (mu::string (U"thing"), context, expression);
    map.fill_reference (mu::string (U"thing"), context, expression);
    map.insert_global (&errors, mu::string (U"thing"), &node);
    EXPECT_TRUE (errors.errors.empty ());
    EXPECT_TRUE (expression.dependencies.size () == 2);
    EXPECT_TRUE (expression.dependencies [0] == &node);
    EXPECT_TRUE (expression.dependencies [1] == &node);
}

// Check that there are no errors when there are no names
TEST (io_test, name_map15)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::expression expression;
    mu::core::node node;
    map.finalize (&errors);
    EXPECT_TRUE (errors.errors.empty ());
}

// Check that there are no errors when everything is resolved
TEST (io_test, name_map16)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::expression expression;
    mu::core::node node;
    map.insert_global (&errors, mu::string (U"thing"), &node);
    map.fill_reference (mu::string (U"thing"), context, expression);
    map.finalize (&errors);
    EXPECT_TRUE (errors.errors.empty ());
}

// Check that there are errors when there are unresolved references
TEST (io_test, name_map17)
{
    mu::core::errors::error_list errors;
    mu::io::analyzer::name_map map;
    mu::io::debugging::context context;
    mu::core::expression expression;
    mu::core::node node;
    map.fill_reference (mu::string (U"thing"), context, expression);
    map.finalize (&errors);
    EXPECT_TRUE (!errors.errors.empty ());
}