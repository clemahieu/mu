#pragma once

#include <lambda_p/core/target.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class target;
		class expression;
		class gather
		{
		public:
			gather (boost::shared_ptr <lambda_p::core::target> target_a, size_t size_a);
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments, size_t sequence) override;
			std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
			boost::shared_ptr <lambda_p::core::target> target;
			size_t remaining;
		};
	}
}

