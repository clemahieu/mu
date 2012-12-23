#pragma once

#include <cstring>

#include <mu/io/lexer_state.h>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class identifier;
			class hex_code : public mu::io::lexer::state
			{
			public:
				hex_code (size_t digits_a, mu::io::lexer::identifier & identifier_a);
				void lex (boost::circular_buffer <mu::io::lexer::context> & context_a) override;
				mu::io::lexer::identifier & identifier;
				size_t index;
				size_t digits;
				unsigned long result;
			};
		}
	}
}

