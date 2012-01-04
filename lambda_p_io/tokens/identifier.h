#pragma once

#include <iostream>

#include <lambda_p_io/tokens/token.h>

namespace lambda_p_io
{
	namespace tokens
	{
		class identifier : public lambda_p_io::tokens::token
		{	
		public:
			identifier (std::wstring string_a);
			std::wstring token_name () override;
			void operator () (lambda_p_io::tokens::visitor * visitor_a) override;
			std::wstring string;
		};
	}
}