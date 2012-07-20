#pragma once

#include <mu/core/types.h>
#include <mu/io/lexer/character_stream.h>
#include <mu/io/lexer/stream_input.h>
#include <mu/io/lexer/istream_input.h>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class character_stream;
		}
        template <typename T, typename U>
		class source
		{
		public:
            source (T & target_a, U & source_a)
            {
                wchar_t last_char (source_a ());
                while (last_char != L'\uffff')
                {		
                    target_a (last_char);
                    last_char = source_a ();
                }
                target_a (U'\U0000FFFF');
            }
		};
        template <typename T>
        void process (T & target_a, mu::io::lexer::character_stream & source_a)
        {
            mu::io::source <T, mu::io::lexer::character_stream> processor (target_a, source_a);
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
