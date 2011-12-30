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
			std::wstring token_name () override;
			void operator () (lambda_p_serialization::tokens::visitor * visitor_a) override;
			std::wstring string;
		};
	}
}