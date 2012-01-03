#pragma once

#include <lambda_p_serialization/lexer/state.h>

#include <string>

namespace lambda_p_serialization
{
	namespace lexer
	{
		class error : public lambda_p_serialization::lexer::state
		{
		public:
			error (std::wstring message_a);
			void lex (wchar_t character) override;
			std::wstring message;
		};
	}
}
