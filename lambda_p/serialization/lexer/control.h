#pragma once

#include <lambda_p/serialization/lexer/state.h>

namespace lambda_p
{
	namespace serialization
	{
		namespace lexer
		{
			class control : public ::lambda_p::serialization::lexer::state
			{
			public:
				control(void);
				~control(void);
				state_id state_type ();
				bool complete;
			};
		}
	}
}

