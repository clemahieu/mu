#include <mu/core/node.h>
#include <mu/core/node_list.h>

#include <gtest/gtest.h>

TEST (core_test, node1)
{
    mu::core::node node1;
    mu::core::node_list node2;
    auto name1 (node1.name ());
    auto name2 (node2.name ());
    ASSERT_TRUE (name1 != name2);
}