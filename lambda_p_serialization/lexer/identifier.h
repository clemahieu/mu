#pragma once

#include <lambda_p_serialization/lexer/state.h>

#include <string>

namespace lambda_p_serialization
{
	namespace lexer
	{
		class lexer;
		class identifier : public lambda_p_serialization::lexer::state
		{
		public:
			identifier (lambda_p_serialization::lexer::lexer & lexer_a);
			void lex (wchar_t character) override;
			std::wstring string;
			lambda_p_serialization::lexer::lexer & lexer;
		};
	}
}

