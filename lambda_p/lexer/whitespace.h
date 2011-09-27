#pragma once

#include <lambda_p/lexer/state.h>

namespace lambda_p
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

