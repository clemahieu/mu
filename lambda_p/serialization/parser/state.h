#pragma once

namespace lambda_p
{
	namespace serialization
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
				state_result_ref
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
}

