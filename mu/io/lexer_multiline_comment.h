#pragma once

#include <mu/io/lexer_state.h>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class lexer;
			class multiline_comment : public mu::io::lexer::state
			{
			public:
				multiline_comment (mu::io::lexer::lexer & lexer_a);
				void lex (boost::circular_buffer <mu::io::lexer::context> & context_a) override;
				mu::io::lexer::lexer & lexer;
			};
		}
	}
}
