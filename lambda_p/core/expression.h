#pragma once

#include <lambda_p/core/node.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class target;
		class expression : public lambda_p::core::node
		{
		public:
			virtual void operator () (std::vector <boost::shared_ptr <lambda_p::core::node>> & parameters, boost::shared_ptr <lambda_p::core::target> target_a) = 0;
		};
	}
}

