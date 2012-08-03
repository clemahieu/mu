#pragma once

#include <mu/io/debugging/context.h>

#include <gc_allocator.h>

#include <stack>
#include <deque>

namespace mu
{
    namespace core
    {
        namespace errors
        {
            class error_target;
        }
    }
    namespace io
    {
        namespace tokens
        {
            class token;
        }
    }
    namespace script
    {
        namespace parser
        {
            class state;
            class parser
            {
            public:
                parser (mu::core::errors::error_target & errors_a);
                mu::core::errors::error_target & errors;
                void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a);
                std::stack <mu::script::parser::state *, std::deque <mu::script::parser::state *, gc_allocator <mu::script::parser::state *>>> state;
            };
        }
    }
}