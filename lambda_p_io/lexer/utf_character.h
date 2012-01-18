#pragma once

#include <lambda_p_io/lexer/state.h>

namespace lambda_p_io
{
	namespace lexer
	{
		class lexer;
		class utf_character : public lambda_p_io::lexer::state
		{
		public:
			utf_character (lambda_p_io::lexer::lexer & lexer_a);
			void lex (wchar_t character) override;
			void process (wchar_t character);
			void add_nibble (wchar_t character);
			void set_size ();
			void terminate ();
			size_t nibble;
			unsigned char bytes [6];
			size_t last_nibble;
			lambda_p_io::lexer::lexer & lexer;
		};
	}
}
