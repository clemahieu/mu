#pragma once

#include <mu/core/position.h>
#include <mu/io/lexer.state.h>

#include <string>

#include <boost/circular_buffer.hpp>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class lexer;
			class complex_identifier : public mu::io::lexer::state
			{
			public:
				complex_identifier (mu::io::lexer::lexer & lexer_a);
				void lex (wchar_t character) override;
				std::wstring end_token;
				std::wstring data;
				bool have_end_token;
				boost::circular_buffer <wchar_t> last_characters;
				bool match ();
				mu::core::position first;
				mu::core::position last;
				mu::io::lexer::lexer & lexer;
			};
		}
	}
}
