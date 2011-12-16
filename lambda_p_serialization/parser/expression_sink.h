#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p_serialization
{
	namespace core
	{
		class expression;
	}
	namespace parser
	{
		class expression_sink
		{
		public:
			virtual void operator () (boost::shared_ptr <lambda_p::core::expression> expression) = 0;
		};
	}
}
