#pragma once

#include <mu/io/position.h>
#include <mu/io/lexer_state.h>
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
				identifier (mu::io::lexer::lexer & lexer_a, mu::io::position first_a);
				void lex (boost::circular_buffer <mu::io::lexer::context> & context_a) override;
				void add (mu::io::lexer::context const & context_a);
				mu::string string;
				mu::io::position first;
				mu::io::position last;
				mu::io::lexer::lexer & lexer;
			};
		}
	}
}
