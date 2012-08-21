#pragma once

#include <boost/function.hpp>

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
    namespace llvm_
    {
        class ctx;
        namespace cluster
        {
            class node;
        }
        namespace parser
        {
            class state;
            class parser
            {
            public:
                parser (mu::llvm_::ctx & ctx_a, mu::core::errors::error_target & errors_a, boost::function <void (mu::llvm_::cluster::node *)> target_a);
                void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a);
                mu::core::errors::error_target & errors;
                boost::function <void (mu::llvm_::cluster::node *)> target;
                mu::stack <mu::llvm_::parser::state *> state;
                mu::llvm_::ctx & ctx;
            };
        }
    }
}