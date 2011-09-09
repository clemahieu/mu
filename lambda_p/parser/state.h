#pragma once

namespace lambda_p
{
	namespace parser
	{
		enum state_id
		{
			state_error,
			state_begin,
			state_routine,
			state_routine_parameter,
			state_body,
			state_statement,
			state_result_ref,
			state_data,
			state_declaration,
			state_hex_data
		};
		class state
		{
		public:
			state (void);
			~state (void);
			virtual state_id state_type () = 0;
		};
	}
}

