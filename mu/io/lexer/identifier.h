#pragma once

#include <mu/io/debugging/position.h>
#include <mu/io/lexer/state.h>

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
				identifier (mu::io::lexer::lexer & lexer_a, mu::io::debugging::position first_a);
				void lex (wchar_t character) override;
				void add (wchar_t character);
				std::wstring string;
				bool lookahead;
				mu::io::debugging::position lookahead_first;
				mu::io::debugging::position first;
				mu::io::debugging::position last;
				mu::io::lexer::lexer & lexer;
			};
		}
	}
}
