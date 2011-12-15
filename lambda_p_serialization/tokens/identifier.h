#pragma once

#include <iostream>

#include <lambda_p_serialization/tokens/token.h>

namespace lambda_p_serialization
{
	namespace tokens
	{
		class identifier : public lambda_p_serialization::tokens::token
		{	
		public:
			identifier (std::wstring string_a);
			token_ids token_id () override;
			std::wstring token_name () override;
			std::wstring string;
		};
	}
}