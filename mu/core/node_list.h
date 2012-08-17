#pragma once

#include <mu/core/node.h>
#include <mu/core/node_list_iterator.h>

namespace mu
{
    namespace core
    {
        class node_list final : public mu::core::node
        {
        public:
            node_list ();
            template <typename T>
            node_list (T const & begin, T const & end);
            auto begin () -> mu::core::node_list_iterator;
            auto end () -> mu::core::node_list_iterator;
            auto size () -> size_t;
            auto empty () -> bool;
            mu::vector <mu::core::node *> nodes;
        };
    }
}