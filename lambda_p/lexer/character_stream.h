#pragma once

#include <lambda_p/binder/node.h>

namespace lambda_p
{
	namespace lexer
	{
		class character_stream : public lambda_p::binder::node
		{
		public:
			virtual wchar_t operator () () = 0;
		};
	}
}

