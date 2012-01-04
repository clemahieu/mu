#pragma once

#include <lambda_p_io/lexer/state.h>

#include <string>

namespace lambda_p_io
{
	namespace lexer
	{
		class error : public lambda_p_io::lexer::state
		{
		public:
			error (std::wstring message_a);
			void lex (wchar_t character) override;
			std::wstring message;
		};
	}
}
