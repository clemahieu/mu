#pragma once

#include <lambda_p_io/lexer/state.h>

namespace lambda_p_io
{
	namespace lexer
	{
		class identifier;
		class hex_code : public lambda_p_io::lexer::state
		{
		public:
			hex_code (size_t digits_a, lambda_p_io::lexer::identifier & identifier_a);
			void lex (wchar_t character) override;
			lambda_p_io::lexer::identifier & identifier;
			size_t index;
			size_t digits;
			unsigned long result;
		};
	}
}

