#pragma once

#include <lambda_p_serialization/lexer/state.h>

namespace lambda_p_serialization
{
	namespace lexer
	{
		class lexer;
		class control : public lambda_p_serialization::lexer::state
		{
		public:
			control (lambda_p_serialization::lexer::lexer & lexer_a);
			void lex (wchar_t character) override;
			bool complete;
			lambda_p_serialization::lexer::lexer & lexer;
		};
	}
}

