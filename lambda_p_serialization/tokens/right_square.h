#pragma once

#include <lambda_p/tokens/token.h>

#include <string>

namespace lambda_p_serialization
{
	namespace tokens
	{
		class right_square : public lambda_p::tokens::token
		{
		public:
			token_ids token_id () override;
			std::wstring token_name () override;
		};
	}
}

