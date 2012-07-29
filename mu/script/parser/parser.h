#pragma once

#include <mu/io/debugging/context.h>

#include <stack>

namespace mu
{
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
                void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a);
                std::stack <mu::script::parser::state *> state;
            };
        }
    }
}