#pragma once

#include <mu/io/debugging/position.h>
#include <mu/io/lexer/state.h>
#include <mu/core/types.h>

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
				void lex (mu::io::lexer::context const & context_a) override;
				void add (mu::io::lexer::context const & context_a);
				mu::string string;
				bool lookahead;
				mu::io::debugging::position lookahead_first;
				mu::io::debugging::position first;
				mu::io::debugging::position last;
				mu::io::lexer::lexer & lexer;
			};
		}
	}
}
