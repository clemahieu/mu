#pragma once

#include <lambda_p/lexer/state.h>

namespace lambda_p
{
	namespace lexer
	{
		class lexer;
		class singleline_comment : public state
		{
		public:
			singleline_comment (lambda_p::lexer::lexer & lexer_a);
			state_id state_type () override;
			void lex (wchar_t character) override;
			lambda_p::lexer::lexer & lexer;
		};
	}
}

