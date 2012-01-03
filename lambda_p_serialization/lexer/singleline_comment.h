#pragma once

#include <lambda_p_serialization/lexer/state.h>

namespace lambda_p_serialization
{
	namespace lexer
	{
		class lexer;
		class singleline_comment : public lambda_p_serialization::lexer::state
		{
		public:
			singleline_comment (lambda_p_serialization::lexer::lexer & lexer_a);
			void lex (wchar_t character) override;
			lambda_p_serialization::lexer::lexer & lexer;
		};
	}
}

