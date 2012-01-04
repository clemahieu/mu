#pragma once

#include <lambda_p_io/lexer/state.h>

namespace lambda_p_io
{
	namespace lexer
	{
		class lexer;
		class multiline_comment : public lambda_p_io::lexer::state
		{
		public:
			multiline_comment (lambda_p_io::lexer::lexer & lexer_a);
			void lex (wchar_t character) override;
			bool have_colon;
			lambda_p_io::lexer::lexer & lexer;
		};
	}
}

