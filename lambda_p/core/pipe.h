#pragma once

#include <lambda_p/core/input.h>

namespace lambda_p
{
	namespace core
	{
		class pipe : public lambda_p::core::input
		{
		public:
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments);
			boost::shared_ptr <lambda_p::core::input> next;
		};
	}
}

