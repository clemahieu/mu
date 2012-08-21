#pragma once

#include <mu/io/debugging/context.h>

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
        namespace parser
        {
            class parser;
            class state
            {
            public:
                virtual void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) = 0;
                void unexpected_token (mu::llvm_::parser::parser & parser_a, mu::io::tokens::token * token_a, mu::io::debugging::context context_a);
            };
        }
    }
}