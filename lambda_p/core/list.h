#pragma once

#include <lambda_p/core/expression.h>

namespace lambda_p
{
	namespace core
	{
		class list : public lambda_p::core::expression
		{
		public:
			bool resolved ();
			std::vector <boost::shared_ptr <lambda_p::core::expression>> contents;
		};
	}
}

