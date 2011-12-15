#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class expression;
		class connection
		{
		public:
			virtual void operator () (boost::shared_ptr <lambda_p::core::expression> expression_a) = 0;
		};
	}
}

