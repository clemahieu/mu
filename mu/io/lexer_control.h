#pragma once

#include <mu/io/lexer_state.h>
#include <mu/io/position.h>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
            class context;
			class lexer;
			class control : public mu::io::lexer::state
			{
			public:
				control (mu::io::lexer::lexer & lexer_a, mu::io::position first_a);
				void lex (mu::io::lexer::context const & context_a) override;
				mu::io::position first;
				mu::io::lexer::lexer & lexer;
			};
		}
	}
}
