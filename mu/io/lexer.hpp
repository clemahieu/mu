#pragma once

namespace mu
{
    namespace core
    {
        class error;        
    }
    namespace io
    {
        class token;
        typedef struct {mu::io::token * token; mu::core::error * error;} token_result;
        typedef struct {char32_t character; mu::core::error * error;} character_result;
        template <typename T>
        class stream;   
        class token;
        class lexer
        {
        public:
            lexer (mu::io::stream <char32_t> & stream_a);
            mu::io::token_result identifier ();
            mu::io::token_result complex_identifier ();
            void line_comment ();
            mu::core::error * region_comment ();
            mu::io::character_result hex_code (int size_a);
            mu::io::token_result lex ();
            mu::io::stream <char32_t> & stream;
        };
    }
}