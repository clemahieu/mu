#pragma once

#include <lambda_p_io/lexer/state.h>

#include <string>

#include <boost/circular_buffer.hpp>

namespace lambda_p_io
{
	namespace lexer
	{
		class lexer;
		class complex_identifier : public lambda_p_io::lexer::state
		{
		public:
			complex_identifier (lambda_p_io::lexer::lexer & lexer_a);
			void lex (wchar_t character) override;
			std::wstring end_token;
			std::wstring data;
			bool have_end_token;
			boost::circular_buffer <wchar_t> last_characters;
			bool match ();
			lambda_p_io::lexer::lexer & lexer;
		};
	}
}

