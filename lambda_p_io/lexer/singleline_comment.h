#pragma once

#include <lambda_p_io/lexer/state.h>

namespace lambda_p_io
{
	namespace lexer
	{
		class lexer;
		class singleline_comment : public lambda_p_io::lexer::state
		{
		public:
			singleline_comment (lambda_p_io::lexer::lexer & lexer_a);
			void lex (wchar_t character) override;
			lambda_p_io::lexer::lexer & lexer;
		};
	}
}

