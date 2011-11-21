#pragma once

#include <lambda_p/lexer/state.h>

namespace lambda_p
{
	namespace lexer
	{
		class lexer;
		class begin : public lambda_p::lexer::state
		{
		public:		
			begin (lambda_p::lexer::lexer & lexer_a);
			state_id state_type () override;
			void lex (wchar_t character) override;
			lambda_p::lexer::lexer & lexer;
		};
	}
}

