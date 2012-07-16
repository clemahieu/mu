#pragma once

#include <mu/io/debugging/context.h>
#include <mu/io/lexer/state.h>

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
				control (mu::io::lexer::lexer & lexer_a, mu::io::debugging::position first_a);
				void lex (char32_t character) override;
				mu::io::debugging::position first;
				mu::io::lexer::lexer & lexer;
			};
		}
	}
}
