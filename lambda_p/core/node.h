#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class input;
		class expression;
		class node
		{
		public:
			virtual void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> parameters, boost::shared_ptr <lambda_p::core::input> list_a) = 0;
		};
	}
}

