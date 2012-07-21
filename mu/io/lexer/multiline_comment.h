#pragma once

#include <mu/io/lexer/state.h>

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
				void lex (mu::io::lexer::context const & context_a) override;
				bool have_colon;
				mu::io::lexer::lexer & lexer;
			};
		}
	}
}
