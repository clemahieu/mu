#pragma once

#include <io/lexer/state.h>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class lexer;
			class multiline_comment : public mu::io::lexer::state
			{
			public:
				multiline_comment (mu::io::lexer::lexer & lexer_a);
				void lex (wchar_t character) override;
				bool have_colon;
				mu::io::lexer::lexer & lexer;
			};
		}
	}
}
