#pragma once

#include <lambda_p/lexer/state.h>

namespace lambda_p
{
	namespace lexer
	{
		class begin : public lambda_p::lexer::state
		{
		public:				
			state_id state_type ();
		};
	}
}

