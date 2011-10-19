#pragma once

#include <lambda_p/lexer/state.h>

namespace lambda_p
{
	namespace lexer
	{
		class begin : public lambda_p::lexer::state
		{
		public:
			begin(void);
			~begin(void);				
			state_id state_type ();
		};
	}
}

