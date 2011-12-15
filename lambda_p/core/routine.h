#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class input;
		class pipe;
		class routine
		{
		public:
			routine ();
			boost::shared_ptr <lambda_p::core::input> input;
			boost::shared_ptr <lambda_p::core::pipe> output;
		};
	}
}

