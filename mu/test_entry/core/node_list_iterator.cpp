#include <gtest/gtest.h>

#include <mu/core/node_list.h>
#include <mu/core/node_list_iterator.h>
#include <mu/core/node.h>

#include <gc_cpp.h>

TEST (node_list_iterator, empty)
{
    mu::core::node_list list;
    auto begin (list.begin ());
    auto end (list.end ());
    EXPECT_TRUE (begin == end);
    EXPECT_TRUE (list.size () == 0);
}

TEST (node_list_iterator, one)
{
    mu::core::node_list list;
    auto node (new (GC) mu::core::node);
    list.nodes.push_back (node);
    auto begin (list.begin ());
    auto end (list.end ());
    ASSERT_TRUE (begin != end);
    EXPECT_TRUE (*begin == node);
    ++begin;
    EXPECT_TRUE (begin == end);
    EXPECT_TRUE (list.size () == 1);
}

TEST (node_list_iterator, nested)
{
    mu::core::node_list list;
    list.nodes.push_back (new (GC) mu::core::node_list);
    auto begin (list.begin ());
    auto end (list.end ());
    EXPECT_TRUE (begin == end);
    EXPECT_TRUE (list.size () == 0);
}

TEST (node_list_iterator, nested_one)
{
    mu::core::node_list list;
    auto inner (new (GC) mu::core::node_list);
    list.nodes.push_back (inner);
    auto node (new (GC) mu::core::node);
    inner->nodes.push_back (node);
    auto begin (list.begin ());
    auto end (list.end ());
    ASSERT_TRUE (begin != end);
    EXPECT_TRUE (*begin == node);
    ++begin;
    EXPECT_TRUE (begin == end);
    EXPECT_TRUE (list.size () == 1);
}

TEST (node_list_iterator, nested_after)
{
    mu::core::node_list list;
    auto inner (new (GC) mu::core::node_list);
    auto node1 (new (GC) mu::core::node);
    list.nodes.push_back (node1);
    list.nodes.push_back (inner);
    auto node2 (new (GC) mu::core::node);
    inner->nodes.push_back (node2);
    auto begin (list.begin ());
    auto end (list.end ());
    ASSERT_TRUE (begin != end);
    EXPECT_TRUE (*begin == node1);
    ++begin;
    ASSERT_TRUE (begin != end);
    EXPECT_TRUE (*begin == node2);
    ++begin;
    EXPECT_TRUE (begin == end);
    EXPECT_TRUE (list.size () == 2);
}