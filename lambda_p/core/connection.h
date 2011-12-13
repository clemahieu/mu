#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class target;
		class expression;
		class connection
		{
		public:
			virtual void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> parameters, boost::shared_ptr <lambda_p::core::target> list_a) = 0;
		};
	}
}

