#pragma once

#include <mu/io/lexer/context.h>
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
				control (mu::io::lexer::lexer & lexer_a, mu::io::position first_a);
				void lex (mu::io::lexer::context const & context_a) override;
				mu::io::position first;
				mu::io::lexer::lexer & lexer;
			};
		}
	}
}
