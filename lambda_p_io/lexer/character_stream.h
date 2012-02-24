#pragma once

#include <core/node.h>

namespace lambda_p_io
{
	namespace lexer
	{
		class character_stream : public mu::core::node
		{
		public:
			virtual wchar_t operator () () = 0;
		};
	}
}

