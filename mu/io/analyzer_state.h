#pragma once

#include <mu/io/context.h>

namespace mu
{
    namespace io
    {
        namespace tokens
        {
            class token;
        }
        namespace analyzer
        {
            class state
            {
            public:
                virtual void operator () (mu::io::tokens::token const & token_a) = 0;
            };
        }
    }
}