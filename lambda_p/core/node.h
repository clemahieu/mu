#pragma once

#include <lambda_p/core/expression.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class target;
		class node : public lambda_p::core::expression
		{
		public:
			virtual void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> & parameters, boost::shared_ptr <lambda_p::core::target> target_a) = 0;
		};
	}
}

