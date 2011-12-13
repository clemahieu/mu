#pragma once

namespace lambda_p
{
	namespace tokens
	{
		class token;
	}
	namespace parser
	{
		class state
		{
		public:
			virtual void parse (lambda_p::tokens::token * token) = 0;
		};
	}
}

