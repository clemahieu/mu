#pragma once

#include <lambda_p/serialization/parser/state.h>

namespace lambda_p
{
	namespace serialization
	{
		namespace parser
		{
			class routine : public state
			{
			public:
				routine(void);
				~routine(void);
				state_id state_type ();
				bool parsed_routine;
			};
		}
	}
}

