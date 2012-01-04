#pragma once

#include <lambda_p_io/lexer/state.h>

namespace lambda_p_io
{
	namespace lexer
	{
		class lexer;
		class begin : public lambda_p_io::lexer::state
		{
		public:		
			begin (lambda_p_io::lexer::lexer & lexer_a);
			void lex (wchar_t character) override;
			lambda_p_io::lexer::lexer & lexer;
		};
	}
}

