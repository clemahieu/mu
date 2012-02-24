#pragma once

#include <io/lexer/state.h>

#include <string>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class error : public mu::io::lexer::state
			{
			public:
				void lex (wchar_t character) override;
			};
		}
	}
}