#pragma once

#include <mu/io/lexer/state.h>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class lexer;
			class begin : public mu::io::lexer::state
			{
			public:		
				begin (mu::io::lexer::lexer & lexer_a);
				void lex (wchar_t character) override;
				mu::io::lexer::lexer & lexer;
			};
		}
	}
}
