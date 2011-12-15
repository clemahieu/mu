#pragma once

#include <string>

namespace lambda_p_serialization
{
	namespace tokens
	{
		enum token_ids
		{
			token_id_complex_identifier,
			token_id_identifier,
			token_id_divider,
			token_id_left_square,
			token_id_right_square,
            token_id_stream_end
		};
		class token
		{
		public:
			virtual token_ids token_id () = 0;
			virtual std::wstring token_name () = 0;
		};
	}
}

