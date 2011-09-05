#pragma once

#include <lambda_p/serialization/lexer/state.h>

namespace lambda_p
{
	namespace serialization
	{
		namespace lexer
		{
			class singleline_comment : public state
			{
			public:
				singleline_comment(void);
				~singleline_comment(void);
				state_id state_type ();
			};
		}
	}
}

