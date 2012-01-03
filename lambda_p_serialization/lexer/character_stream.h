#pragma once

#include <lambda_p/core/expression.h>

namespace lambda_p_serialization
{
	namespace lexer
	{
		class character_stream : public lambda_p::core::expression
		{
		public:
			virtual wchar_t operator () () = 0;
		};
	}
}

