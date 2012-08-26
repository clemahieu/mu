#pragma once

#include <mu/io/lexer_state.h>

#include <string>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class error : public mu::io::lexer::state
			{
			public:
				void lex (mu::io::lexer::context const & context_a) override;
			};
		}
	}
}