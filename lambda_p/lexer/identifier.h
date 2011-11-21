#pragma once

#include <lambda_p/lexer/state.h>

#include <string>

namespace lambda_p
{
	namespace lexer
	{
		class lexer;
		class identifier : public state
		{
		public:
			identifier (lambda_p::lexer::lexer & lexer_a);
			state_id state_type () override;
			void lex (wchar_t character) override;
			std::wstring string;
			lambda_p::lexer::lexer & lexer;
		};
	}
}

