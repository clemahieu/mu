#pragma once

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
                topology (std::vector <mu::script::runtime::expression *, gc_allocator <mu::script::runtime::expression *>> & expressions_a, mu::script::runtime::routine * routine_a, mu::core::errors::error_target & errors_a);
                void operator () ();
                void recurse (mu::script::runtime::expression * expression_a);
                std::vector <mu::script::runtime::expression *, gc_allocator <mu::script::runtime::expression *>> & expressions;
                mu::script::runtime::routine * routine;
                mu::core::errors::error_target & errors;
                std::set <mu::script::runtime::expression *, std::less <mu::script::runtime::expression *>, gc_allocator <mu::script::runtime::expression *>> already;
                std::set <mu::script::runtime::expression *, std::less <mu::script::runtime::expression *>, gc_allocator <mu::script::runtime::expression *>> path;
            };
        }
    }
}