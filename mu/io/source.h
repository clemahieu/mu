#pragma once

#include <mu/core/types.h>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class character_stream;
		}
		class source
		{
		public:
			void operator () ();
			virtual void operator () (char32_t char_a) = 0;
			void operator () (mu::string & string);
			void operator () (mu::string const & string);
			void operator () (char32_t const * string);
            void operator () (mu::io::lexer::character_stream * source);
            void process_string (mu::string const & string);
		};
	}
}
