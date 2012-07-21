#pragma once

#include <mu/io/debugging/position.h>

namespace mu
{
    namespace io
    {
        namespace lexer
        {
            class character_stream;
            class context
            {
            public:
                context ();
                context (mu::io::debugging::position position_a, char32_t character_a);
                mu::io::debugging::position position;
                char32_t character;
            };            
        }
    }
}