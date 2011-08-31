#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>
#include <string>

#include <lambda_p/core/node.h>
#include <lambda_p/core/statement.h>

namespace lambda_p
{
	namespace core
	{
		class routine
		{
		public:
			routine ();
			~routine (void);
			::lambda_p::core::node declaration;
			::std::vector < ::lambda_p::core::node *> parameters;
			::std::vector < ::lambda_p::core::statement> body;
			::std::vector < ::lambda_p::core::identifier> identifiers;
		};
	}
}
