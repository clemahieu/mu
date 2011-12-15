#pragma once

#include <lambda_p_serialization/lexer/state.h>

namespace lambda_p_serialization
{
	namespace lexer
	{
		class lexer;
		class multiline_comment : public lambda_p_serialization::lexer::state
		{
		public:
			multiline_comment (lambda_p_serialization::lexer::lexer & lexer_a);
			void lex (wchar_t character) override;
			bool have_colon;
			lambda_p_serialization::lexer::lexer & lexer;
		};
	}
}

