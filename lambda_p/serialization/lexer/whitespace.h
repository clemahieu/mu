#pragma once

#include <lambda_p/serialization/lexer/state.h>

namespace lambda_p
{
	namespace serialization
	{
		namespace lexer
		{
			class whitespace : public state
			{
			public:
				whitespace(void);
				~whitespace(void);	
				state_id state_type ();
			};
		}
	}
}

