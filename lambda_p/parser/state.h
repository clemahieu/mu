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
			state_statement,
			state_data,
			state_association,
            state_finished
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

