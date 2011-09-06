#pragma once

#include <lambda_p/serialization/lexer/state.h>

#include <string>

namespace lambda_p
{
	namespace serialization
	{
		namespace lexer
		{
			class error : public ::lambda_p::serialization::lexer::state
			{
			public:
				error(::std::wstring message_a);
				~error(void);
				state_id state_type ();
				::std::wstring message;
			};
		}
	}
}
