#pragma once

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class node;
		class association
		{
		public:
            ::std::vector < ::lambda_p::core::node *> results;
			::std::vector < ::lambda_p::core::node *> parameters;
		};
	}
}

