#pragma once

#include <mu/core/types.h>
#include <mu/io/lexer_character_stream.h>
#include <mu/io/lexer_stream_input.h>
#include <mu/io/lexer_istream_input.h>
#include <mu/io/lexer_context.h>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class character_stream;
		}
        template <typename T>
        void process (T & target_a, mu::io::lexer::character_stream & source_a)
        {
            mu::io::lexer::context context;
            char32_t last_char (U' ');
            while (last_char != U'\U0000FFFF')
            {		
                last_char = source_a ();
                context.character = last_char;
                target_a (context);
                ++context.position.character;
                if (last_char == U'\n')
                {
                    context.position.column = 1;
                    ++context.position.row;
                }
                else
                {
                    ++context.position.column;
                }
            }
        }
        template <typename T>
        void process (T & target_a, mu::string const & source_a)
        {
            mu::stringstream stream (source_a);
            mu::io::lexer::stream_input input (stream);
            process (target_a, input);
        }
        template <typename T>
        void process (T & target_a, char32_t const * const source_a)
        {
            mu::string string (source_a);
            process (target_a, string);
        }
        template <typename T>
        void process (T & target_a, mu::stringstream & source_a)
        {
            mu::io::lexer::stream_input input (source_a);
            process (target_a, input);
        }
        template <typename T>
        void process (T & target_a, std::istream & source_a)
        {
            mu::io::lexer::istream_input input (source_a);
            process (target_a, input);
        }
	}
}
