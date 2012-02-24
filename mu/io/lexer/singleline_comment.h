#pragma once

#include <mu/io/lexer/state.h>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class lexer;
			class singleline_comment : public mu::io::lexer::state
			{
			public:
				singleline_comment (mu::io::lexer::lexer & lexer_a);
				void lex (wchar_t character) override;
				mu::io::lexer::lexer & lexer;
			};
		}
	}
}
