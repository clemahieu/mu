#pragma once

#include <lambda_p/lexer/state.h>

namespace lambda_p
{
	namespace lexer
	{
		class singleline_comment : public state
		{
		public:
			state_id state_type ();
		};
	}
}

