#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class target;
		class pipe;
		class routine
		{
		public:
			routine ();
			boost::shared_ptr <lambda_p::core::target> input;
			boost::shared_ptr <lambda_p::core::pipe> output;
		};
	}
}

