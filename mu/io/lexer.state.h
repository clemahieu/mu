#pragma once

#include <wchar.h>

namespace mu
{
	namespace io
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
}
