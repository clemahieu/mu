#pragma once

#include <lambda_p_serialization/tokens/token.h>

#include <string>

namespace lambda_p_serialization
{
	namespace tokens
	{
		class right_square : public lambda_p_serialization::tokens::token
		{
		public:
			lambda_p_serialization::tokens::token_ids token_id () override;
			std::wstring token_name () override;
		};
	}
}

