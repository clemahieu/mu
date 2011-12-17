#pragma once

#include <lambda_p/core/target.h>

namespace lambda_p
{
	namespace core
	{
		class call : public lambda_p::core::target
		{
		public:
			call (boost::shared_ptr <lambda_p::core::target> target_a);
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments) override;
			boost::shared_ptr <lambda_p::core::target> target;
		};
	}
}

