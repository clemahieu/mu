#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class tee;
		class node;
		class fixed
		{
		public:
			fixed ();
			void operator () ();
			boost::shared_ptr <lambda_p::core::tee> target;
			std::vector <boost::shared_ptr <lambda_p::core::node>> arguments;
		};
	}
}

