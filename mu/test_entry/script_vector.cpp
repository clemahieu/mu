#include <gtest/gtest.h>

#include <mu/script/context.h>
#include <mu/script/vector_size.h>
#include <mu/script/vector_create.h>
#include <mu/script/vector_item.h>
#include <mu/script/vector_node.h>
#include <mu/script/integer_node.h>

// Empty vector node construction
TEST (script_test, vector1)
{
    mu::script::vector::node node;
}

// Creating empty vector through create
TEST (script_test, vector2)
{
    mu::script::context context;
    mu::script::vector::create create;
    context.push (&create);
    auto valid (context ());
    ASSERT_TRUE (valid);
    ASSERT_TRUE (context.working_size () == 1);
    auto node (dynamic_cast <mu::script::vector::node *> (context.working(0)));
    ASSERT_TRUE (node != nullptr);
    ASSERT_TRUE (node->vector.size () == 0);
}

// Vector with one node
TEST (script_test, vector3)
{
    mu::script::context context;
    mu::script::vector::create create;
    context.push (&create);
    mu::core::node node1;
    context.push (&node1);
    auto valid (context ());
    ASSERT_TRUE (valid);
    ASSERT_TRUE (context.working_size () == 1);
    auto node (dynamic_cast <mu::script::vector::node *> (context.working (0)));
    ASSERT_TRUE (node != nullptr);
    ASSERT_TRUE (node->vector.size () == 1);
    ASSERT_TRUE (node->vector [0] == &node1);
}

// Vector with two nodes
TEST (script_test, vector4)
{
    mu::script::context context;
    mu::script::vector::create create;
    context.push (&create);
    mu::core::node node1;
    context.push (&node1);
    mu::core::node node2;
    context.push (&node2);
    auto valid (context ());
    ASSERT_TRUE (valid);
    ASSERT_TRUE (context.working_size () == 1);
    auto node (dynamic_cast <mu::script::vector::node *> (context.working(0)));
    ASSERT_TRUE (node != nullptr);
    ASSERT_TRUE (node->vector.size () == 2);
    ASSERT_TRUE (node->vector [0] == &node1);
    ASSERT_TRUE (node->vector [1] == &node2);
}

// Vector size
TEST (script_test, vector5)
{
    mu::script::context context;
    mu::script::vector::node node;
    mu::core::node node1;
    mu::core::node node2;
    node.vector.push_back (&node1);
    node.vector.push_back (&node2);
    mu::script::vector::size size;
    context.push (&size);
    context.push (&node);
    auto valid (context ());
    ASSERT_TRUE (valid);
    ASSERT_TRUE (context.working_size () == 1);
    auto node3 (dynamic_cast <mu::script::integer::node *> (context.working(0)));
    ASSERT_TRUE (node3 != nullptr);
    ASSERT_TRUE (node3->value == 2);
}

// Vector item 1 inbounds
TEST (script_test, vector6)
{
    mu::script::context context;
    mu::script::vector::node node;
    mu::core::node node1;
    mu::core::node node2;
    node.vector.push_back (&node1);
    node.vector.push_back (&node2);
    mu::script::vector::item item;
    mu::script::integer::node index1 (0);
    context.push (&item);
    context.push (&node);
    context.push (&index1);
    auto valid1 (context ());
    ASSERT_TRUE (valid1);
    ASSERT_TRUE (context.working_size () == 1);
    ASSERT_TRUE (context.working(0) == &node1);
}

// Vector item 2 inbounds
TEST (script_test, vector7)
{
    mu::script::context context;
    mu::script::vector::node node;
    mu::core::node node1;
    mu::core::node node2;
    node.vector.push_back (&node1);
    node.vector.push_back (&node2);
    mu::script::vector::item item;
    mu::script::integer::node index2 (1);
    context.push (&item);
    context.push (&node);
    context.push (&index2);
    auto valid2 (context ());
    ASSERT_TRUE (valid2);
    ASSERT_TRUE (context.working_size () == 1);
    ASSERT_TRUE (context.working(0) == &node2);
}

// Vector item out of bounds
TEST (script_test, vector8)
{
    mu::script::context context;
    mu::script::vector::node node;
    mu::core::node node1;
    mu::core::node node2;
    node.vector.push_back (&node1);
    node.vector.push_back (&node2);
    mu::script::vector::item item;
    mu::script::integer::node index3 (2);
    context.push (&item);
    context.push (&node);
    context.push (&index3);
    auto valid3 (context ());
    ASSERT_TRUE (!valid3);
}