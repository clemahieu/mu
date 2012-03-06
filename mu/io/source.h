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
			source (boost::function <void (wchar_t char_a)> target_a);
			void operator () ();
			void operator () (wchar_t char_a);
			void operator () (std::wstring & string);
			void operator () (std::wstring const & string);
			void operator () (wchar_t const * string);
			void operator () (boost::shared_ptr <mu::io::lexer::character_stream> source);
            void operator << (boost::shared_ptr <mu::io::lexer::character_stream> source);
            void process_string (std::wstring const & string);
			boost::function <void (wchar_t char_a)> target;
		};
	}
}
