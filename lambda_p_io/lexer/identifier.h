#pragma once

#include <lambda_p/position.h>
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
			identifier (lambda_p_io::lexer::lexer & lexer_a, lambda_p::position first_a);
			void lex (wchar_t character) override;
			void add (wchar_t character);
			std::wstring string;
			bool lookahead;
			lambda_p::position lookahead_first;
			lambda_p::position first;
			lambda_p::position last;
			lambda_p_io::lexer::lexer & lexer;
		};
	}
}

