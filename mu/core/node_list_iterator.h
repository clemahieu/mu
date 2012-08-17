#pragma once

#include <cstddef>
namespace mu
{
    namespace core
    {
        class node;
        class node_list;
        class node_list_iterator
        {
        public:
            node_list_iterator (mu::core::node_list_iterator const && other);
            node_list_iterator (mu::core::node_list & list_a);
            node_list_iterator (mu::core::node_list & list_a, void * nothing); // end
            auto operator == (mu::core::node_list_iterator const & other) const -> bool;
            auto operator != (mu::core::node_list_iterator const & other) const -> bool;
            auto operator ++ () -> mu::core::node_list_iterator &;
            auto operator * () -> mu::core::node *;
            auto nested () const -> bool;
            auto advance () -> void;
            mu::core::node_list & list;
            size_t position;
            node_list_iterator * inner_cursor;
            node_list_iterator * inner_end;
        };
    }
}