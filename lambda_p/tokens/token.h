#pragma once

#include <cstring>

namespace lambda_p
{
	namespace tokens
	{
		enum token_ids
		{
			token_id_complex_identifier,
			token_id_declaration,
			token_id_identifier,
			token_id_routine_end,
			token_id_data,
			token_id_statement_end,
			token_id_connector
		};
		class token
		{
		public:
			token(void);
			~token(void);
			virtual token_ids token_id () = 0;
		};
	}
}

