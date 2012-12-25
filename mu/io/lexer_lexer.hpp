#pragma once

namespace mu
{
    namespace io
    {
        template <typename T>
        class buffer;
        namespace lexer
        {
            class lexer
            {
            public:
                void lex (mu::io::buffer <char32_t> & buffer_a);
            };
        }
    }
}