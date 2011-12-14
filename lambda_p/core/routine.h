#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class scatter;
		class pipe;
		class gather;
		class routine
		{
		public:
			routine ();
			boost::shared_ptr <lambda_p::core::scatter> input;
			boost::shared_ptr <lambda_p::core::pipe> output;
		};
	}
}

