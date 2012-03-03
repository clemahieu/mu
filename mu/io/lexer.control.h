#pragma once

#include <mu/core/position.h>
#include <mu/io/lexer.state.h>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class lexer;
			class control : public mu::io::lexer::state
			{
			public:
				control (mu::io::lexer::lexer & lexer_a, mu::core::position first_a);
				void lex (wchar_t character) override;
				mu::core::position first;
				mu::io::lexer::lexer & lexer;
			};
		}
	}
}
