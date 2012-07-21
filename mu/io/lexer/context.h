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
                mu::io::debugging::position position;
                char32_t character;
                
            };            
        }
    }
}