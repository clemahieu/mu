#pragma once

namespace lambda_p
{
	namespace lexer
	{
		class state
		{
		public:
			virtual void lex (wchar_t character) = 0;
		};
	}
}
