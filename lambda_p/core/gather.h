#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class target;
		class input;
		class expression;
		class gather
		{
		public:
			gather (boost::shared_ptr <lambda_p::core::input> target_a, size_t size_a);
			void operator () (boost::shared_ptr <lambda_p::core::expression> expression_a, size_t index_a);
			std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
			boost::shared_ptr <lambda_p::core::input> target;
			size_t remaining;
		};
	}
}

