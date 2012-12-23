#pragma once

#include <mu/io/context.h>
#include <mu/io/lexer_state.h>
#include <mu/core/types.h>

#include <boost/circular_buffer.hpp>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class lexer;
			class complex_identifier : public mu::io::lexer::state
			{
			public:
				complex_identifier (mu::io::lexer::lexer & lexer_a, mu::io::position first_a);
				void lex (boost::circular_buffer <mu::io::lexer::context> & context_a) override;
				mu::string end_token;
				mu::string data;
				bool have_end_token;
				boost::circular_buffer <char32_t> last_characters;
				bool match ();
				mu::io::position first;
				mu::io::lexer::lexer & lexer;
			};
		}
	}
}
