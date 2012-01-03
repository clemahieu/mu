#pragma once

#include <string>

namespace lambda_p_serialization
{
	namespace tokens
	{
		class visitor;
		class token
		{
		public:
			virtual std::wstring token_name () = 0;
			virtual void operator () (lambda_p_serialization::tokens::visitor * visitor_a) = 0;
		};
	}
}

