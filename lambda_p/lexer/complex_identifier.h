#pragma once

#include <lambda_p/lexer/state.h>

#include <string>

#include <boost/circular_buffer.hpp>

namespace lambda_p
{
	namespace lexer
	{
		class lexer;
		class complex_identifier : public state
		{
		public:
			complex_identifier (lambda_p::lexer::lexer & lexer_a);
			state_id state_type () override;
			void lex (wchar_t character) override;
			std::wstring end_token;
			std::wstring data;
			bool have_end_token;
			boost::circular_buffer <wchar_t> last_characters;
			bool match ();
			lambda_p::lexer::lexer & lexer;
		};
	}
}

