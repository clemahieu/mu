#pragma once

#include <lambda_p/serialization/lexer/state.h>

namespace lambda_p
{
	namespace serialization
	{
		namespace lexer
		{
			class multiline_comment : public state
			{
			public:
				multiline_comment(void);
				~multiline_comment(void);
				state_id state_type ();
				bool have_semicolon;
			};
		}
	}
}

