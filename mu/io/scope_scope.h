#pragma once

#include <mu/core/types.h>

namespace mu
{
    namespace core
    {
        class node;
        class node_list;
        namespace errors
        {
            class error_target;
        }
    }
    namespace io
    {
        namespace scope
        {
            class scope
            {
            public:
                virtual bool reserve (mu::core::errors::error_target & errors_a, mu::string const & name_a) = 0;
                virtual bool fill (mu::string const & name_a, mu::core::node_list & target_a) = 0;
                virtual void pass (mu::multimap <mu::string, mu::core::node_list *> const & unresolved_a) = 0;
            };
        }
    }
}