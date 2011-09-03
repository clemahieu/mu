#pragma once

namespace lambda_p
{
	namespace tokens
	{
		enum token_ids
		{
			token_id_complex_identifier,
			token_id_declaration,
			token_id_error,
			token_id_hex_data_token,
			token_id_identifier,
			token_id_routine_end,
			token_id_data_token,
			token_id_statement_end
		};
		class token
		{
		public:
			token(void);
			~token(void);
			virtual size_t token_id () = 0;
		};
	}
}

