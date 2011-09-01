#pragma once

#include <vector>

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
			size_t parameters;
			::std::vector < ::lambda_p::core::statement> statements;
		};
	}
}
