#pragma once

#include <lambda_p/lexer/state.h>

namespace lambda_p
{
	namespace lexer
	{
		class control : public ::lambda_p::lexer::state
		{
		public:
			control(void);
			~control(void);
			state_id state_type ();
			bool complete;
		};
	}
}

