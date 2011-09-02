#pragma once

#include <iostream>

#include <lambda_p/tokens/token.h>

namespace lambda_p
{
	namespace tokens
	{
		class identifier : public ::lambda_p::tokens::token
		{	
		public:
			identifier (::std::wstring string_a);
			~identifier (void);
		private:
			::std::wstring string;
		};
	}
}