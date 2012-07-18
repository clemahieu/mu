#pragma once

#include <mu/io/debugging/context.h>

namespace mu
{
    namespace io
    {
        namespace lexer
        {
            class character_stream;
            class context
            {
                mu::io::debugging::context context;
                char32_t character;
            };            
        }
    }
}