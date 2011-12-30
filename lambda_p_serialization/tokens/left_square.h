#pragma once

#include <lambda_p_serialization/tokens/token.h>

#include <string>

namespace lambda_p_serialization
{
	namespace tokens
	{
		class left_square : public lambda_p_serialization::tokens::token
		{
		public:
			std::wstring token_name () override;
			void operator () (lambda_p_serialization::tokens::visitor * visitor_a) override;
		};
	}
}

