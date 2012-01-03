#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class tee;
		class expression;
		class fixed
		{
		public:
			fixed ();
			void operator () ();
			boost::shared_ptr <lambda_p::core::tee> target;
			std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
		};
	}
}

