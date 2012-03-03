#pragma once

#include <mu/core/position.h>
#include <mu/io/lexer.state.h>

#include <string>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class lexer;
			class identifier : public mu::io::lexer::state
			{
			public:
				identifier (mu::io::lexer::lexer & lexer_a, mu::core::position first_a);
				void lex (wchar_t character) override;
				void add (wchar_t character);
				std::wstring string;
				bool lookahead;
				mu::core::position lookahead_first;
				mu::core::position first;
				mu::core::position last;
				mu::io::lexer::lexer & lexer;
			};
		}
	}
}
