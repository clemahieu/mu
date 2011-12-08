#pragma once

#include <lambda_p/core/node.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class list;
		class routine : public lambda_p::core::node
		{
		public:
			routine ();
			std::vector <boost::shared_ptr <lambda_p::core::node>> surface;
			boost::shared_ptr <lambda_p::core::list> expression;
		};
	}
}
