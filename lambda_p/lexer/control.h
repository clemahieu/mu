#pragma once

#include <lambda_p/lexer/state.h>

namespace lambda_p
{
	namespace lexer
	{
		class lexer;
		class control : public lambda_p::lexer::state
		{
		public:
			control (lambda_p::lexer::lexer & lexer_a);
			state_id state_type () override;
			void lex (wchar_t character) override;
			bool complete;
			lambda_p::lexer::lexer & lexer;
		};
	}
}

