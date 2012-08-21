#pragma once

#include <mu/core/types.h>

#include <cstddef>
#include <iterator>

namespace mu
{
    namespace core
    {
        class node;
        class node_list;
        class node_list_iterator
        {
        public:
            typedef typename std::input_iterator_tag iterator_category;
            typedef typename mu::core::node * value_type;
            typedef typename mu::vector <mu::core::node *>::difference_type difference_type;
            typedef typename mu::vector <mu::core::node *>::pointer pointer;
            typedef typename mu::vector <mu::core::node *>::reference reference;
            node_list_iterator (mu::core::node_list_iterator const && other);
            node_list_iterator (mu::core::node_list_iterator const & other);
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