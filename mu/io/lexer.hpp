#pragma once

#include <mu/io/tokens.hpp>

namespace mu
{
    namespace core
    {
        class error;        
    }
    namespace io
    {
        class token;
        struct token_result
        {
            ~token_result ();
            mu::io::token * token;
            mu::core::error * error;
        };
        struct character_result
        {
            ~character_result ();
            char32_t character;
            mu::core::error * error;
        };
		class string_range
		{
		public:
			string_range (std::string const &);
			string_range (char const * const &);
			string_range (uint8_t const *, uint8_t const *);
			mu::io::string_range substr (size_t) const;
			mu::io::string_range substr (size_t, size_t) const;
			uint8_t const * begin ();
			uint8_t const * end ();
			bool operator == (mu::io::string_range const &) const;
			bool operator != (mu::io::string_range const &) const;
			bool empty () const;
			size_t size () const;
			char32_t operator [] (size_t) const;
			uint8_t const * begin_m;
			uint8_t const * end_m;
		};
        class token;
        class lexer
        {
        public:
            lexer (mu::io::string_range const &);
            mu::io::token_result identifier ();
            mu::io::token_result complex_identifier ();
            void line_comment ();
            void consume (size_t size_a);
            mu::core::position position;
            mu::core::error * region_comment ();
            mu::io::character_result hex_code (int size_a);
            mu::io::token_result lex ();
            mu::io::string_range source;
        };
    }
}