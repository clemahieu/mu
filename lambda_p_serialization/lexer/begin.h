#pragma once

#include <lambda_p_serialization/lexer/state.h>

namespace lambda_p_serialization
{
	namespace lexer
	{
		class lexer;
		class begin : public lambda_p_serialization::lexer::state
		{
		public:		
			begin (lambda_p_serialization::lexer::lexer & lexer_a);
			void lex (wchar_t character) override;
			lambda_p_serialization::lexer::lexer & lexer;
		};
	}
}

