#pragma once

#include <boost/function.hpp>

#include <vector>
#include <set>

#include <gc_allocator.h>

namespace mu
{
    namespace core
    {
        namespace errors
        {
            class error_target;
        }
    }
    namespace script
    {
        namespace runtime
        {
            class expression;
            class routine;
        }
        namespace parser
        {
            class topology
            {
            public:
                topology (mu::script::runtime::expression * root, boost::function <void (mu::script::runtime::expression *)> target_a, mu::core::errors::error_target & errors_a);
                void recurse (mu::script::runtime::expression * expression_a);
                boost::function <void (mu::script::runtime::expression *)> target;
                mu::core::errors::error_target & errors;
                std::set <mu::script::runtime::expression *, std::less <mu::script::runtime::expression *>, gc_allocator <mu::script::runtime::expression *>> already;
                std::set <mu::script::runtime::expression *, std::less <mu::script::runtime::expression *>, gc_allocator <mu::script::runtime::expression *>> path;
            };
        }
    }
}