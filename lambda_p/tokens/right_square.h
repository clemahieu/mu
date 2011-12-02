#pragma once

#include <lambda_p/tokens/token.h>

namespace lambda_p
{
	namespace tokens
	{
		class right_square : public lambda_p::tokens::token
		{
		public:
			token_ids token_id () override;
		};
	}
}

