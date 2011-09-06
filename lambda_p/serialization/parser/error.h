#pragma once

#include <lambda_p/serialization/parser/state.h>

namespace lambda_p
{
	namespace serialization
	{
		namespace parser
		{
			class error : public ::lambda_p::serialization::parser::state
			{
			public:
				error(void);
				~error(void);
				state_id state_type ();
			};
		}
	}
}
