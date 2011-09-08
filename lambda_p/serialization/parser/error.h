#pragma once

#include <lambda_p/serialization/parser/state.h>

#include <string>

namespace lambda_p
{
	namespace serialization
	{
		namespace parser
		{
			class error : public ::lambda_p::serialization::parser::state
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