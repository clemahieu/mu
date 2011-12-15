#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class expression;
		class target
		{
		public:
			virtual void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments) = 0;
		};
	}
}

