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
			void lex (wchar_t character) override;
		};
	}
}
