#pragma once

#include <core/position.h>
#include <lambda_p_io/lexer/state.h>

#include <string>

namespace lambda_p_io
{
	namespace lexer
	{
		class lexer;
		class identifier : public lambda_p_io::lexer::state
		{
		public:
			identifier (lambda_p_io::lexer::lexer & lexer_a, mu::core::position first_a);
			void lex (wchar_t character) override;
			void add (wchar_t character);
			std::wstring string;
			bool lookahead;
			mu::core::position lookahead_first;
			mu::core::position first;
			mu::core::position last;
			lambda_p_io::lexer::lexer & lexer;
		};
	}
}

