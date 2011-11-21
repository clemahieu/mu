#pragma once

#include <lambda_p/lexer/state.h>

namespace lambda_p
{
	namespace lexer
	{
		class lexer;
		class multiline_comment : public state
		{
		public:
			multiline_comment (lambda_p::lexer::lexer & lexer_a);
			void lex (wchar_t character) override;
			bool have_colon;
			lambda_p::lexer::lexer & lexer;
		};
	}
}

