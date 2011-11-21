#pragma once

#include <lambda_p/lexer/state.h>

#include <string>

namespace lambda_p
{
	namespace lexer
	{
		class error : public lambda_p::lexer::state
		{
		public:
			error(std::wstring message_a);
			state_id state_type () override;
			void lex (wchar_t character) override;
			std::wstring message;
		};
	}
}
