#pragma once

#include <lambda_p/serialization/lexer/state.h>

#include <string>

namespace lambda_p
{
	namespace serialization
	{
		namespace lexer
		{
			class identifier_state : public state
			{
			public:
				identifier_state(void);
				~identifier_state(void);
				state_id state_type ();
				::std::wstring string;
			};
		}
	}
}

