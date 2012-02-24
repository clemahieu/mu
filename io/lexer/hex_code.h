#pragma once

#include <io/lexer/state.h>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class identifier;
			class hex_code : public mu::io::lexer::state
			{
			public:
				hex_code (size_t digits_a, mu::io::lexer::identifier & identifier_a);
				void lex (wchar_t character) override;
				mu::io::lexer::identifier & identifier;
				size_t index;
				size_t digits;
				unsigned long result;
			};
		}
	}
}

