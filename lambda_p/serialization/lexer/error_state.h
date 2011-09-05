#pragma once

#include <lambda_p/serialization/lexer/state.h>

#include <string>

namespace lambda_p
{
	namespace serialization
	{
		namespace lexer
		{
			class error_state : public state
			{
			public:
				error_state(::std::wstring message_a);
				~error_state(void);
				state_id state_type ();
				::std::wstring message;
			};
		}
	}
}
