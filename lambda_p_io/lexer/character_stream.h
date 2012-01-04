#pragma once

#include <lambda_p/core/node.h>

namespace lambda_p_io
{
	namespace lexer
	{
		class character_stream : public lambda_p::core::node
		{
		public:
			virtual wchar_t operator () () = 0;
		};
	}
}

