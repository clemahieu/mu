#pragma once

#include <mu/io/lexer_state.h>

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
				void lex (boost::circular_buffer <mu::io::lexer::context> & context_a) override;
				mu::io::lexer::lexer & lexer;
			};
		}
	}
}
