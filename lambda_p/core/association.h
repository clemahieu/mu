#pragma once

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class declaration;
		class node;
		class association
		{
		public:
            ::std::vector < ::lambda_p::core::declaration *> results;
			::std::vector < ::lambda_p::core::node *> parameters;
		};
	}
}

