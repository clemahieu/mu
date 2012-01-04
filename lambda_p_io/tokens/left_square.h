#pragma once

#include <lambda_p_io/tokens/token.h>

#include <string>

namespace lambda_p_io
{
	namespace tokens
	{
		class left_square : public lambda_p_io::tokens::token
		{
		public:
			std::wstring token_name () override;
			void operator () (lambda_p_io::tokens::visitor * visitor_a) override;
		};
	}
}

