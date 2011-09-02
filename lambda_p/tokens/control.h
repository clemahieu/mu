#pragma once

#include <iostream>

#include <lambda_p/tokens/token.h>

namespace lambda_p
{
	namespace tokens
	{
		class control : public ::lambda_p::tokens::token
		{	
		public:
			control (::std::wstring string_a);
			~control (void);
		private:
			::std::wstring string;
		};
	}
}