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
				state_begin
			};
			class state
			{
			public:
				state (void);
				~state (void);
			};
		}
	}
}

