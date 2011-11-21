#pragma once

namespace lambda_p
{
	namespace lexer
	{
		enum state_id
		{
			state_error,
			state_begin,
			state_control,
			state_identifier,
			state_multiline_comment,
			state_singleline_comment,
			state_complex_identifier
		};
		class state
		{
		public:
			virtual state_id state_type () = 0;
			virtual void lex (wchar_t character) = 0;
		};
	}
}
