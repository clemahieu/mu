#pragma once

#include <mu/io/position.h>

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
                context (mu::io::position position_a, char32_t character_a);
                mu::io::position position;
                char32_t character;
            };            
        }
    }
}