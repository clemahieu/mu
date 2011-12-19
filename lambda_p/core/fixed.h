#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class target;
		class expression;
		class fixed
		{
		public:
			void operator () ();
			boost::shared_ptr <lambda_p::core::target> target;
			std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
		};
	}
}

