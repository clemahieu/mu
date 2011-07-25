#pragma once

#include <vector>

#include <lambda_p/core/statement.h>

namespace lambda_p
{
	namespace core
	{
		class body
		{
		public:
			body (void);
			~body (void);
			::std::vector <::lambda_p::core::statement> statements;
		};
	}
}

