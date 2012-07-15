#pragma once

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

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
			virtual void operator () (wchar_t char_a) = 0;
			void operator () (std::wstring & string);
			void operator () (std::wstring const & string);
			void operator () (wchar_t const * string);
			void operator () (mu::io::lexer::character_stream * source);
            void operator << (mu::io::lexer::character_stream * source);
            void process_string (std::wstring const & string);
		};
	}
}
