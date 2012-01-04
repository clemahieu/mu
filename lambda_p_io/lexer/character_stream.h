#pragma once

#include <lambda_p/node.h>

namespace lambda_p_io
{
	namespace lexer
	{
		class character_stream : public lambda_p::node
		{
		public:
			virtual wchar_t operator () () = 0;
		};
	}
}

