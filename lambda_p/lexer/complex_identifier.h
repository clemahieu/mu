#pragma once

#include <lambda_p/lexer/state.h>

#include <string>

#include <boost/circular_buffer.hpp>

namespace lambda_p
{
	namespace lexer
	{
		class complex_identifier : public state
		{
		public:
			complex_identifier(void);
			~complex_identifier(void);
			state_id state_type ();
			std::wstring end_token;
			std::wstring data;
			bool have_end_token;
			boost::circular_buffer <wchar_t> last_characters;
			bool match ();
		};
	}
}

