#pragma once

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class routine;
		class node;
		class statement
		{
		public:
			statement (::lambda_p::core::routine & routine_a);
			~statement (void);
            ::lambda_p::core::routine & routine;
            size_t index;
            ::std::vector < ::lambda_p::core::node *> arguments;
		};
	}
}
