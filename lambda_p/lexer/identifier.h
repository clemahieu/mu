#pragma once

#include <lambda_p/lexer/state.h>

#include <string>

namespace lambda_p
{
	namespace lexer
	{
		class identifier : public state
		{
		public:
			identifier(void);
			~identifier(void);
			state_id state_type ();
			::std::wstring string;
		};
	}
}

