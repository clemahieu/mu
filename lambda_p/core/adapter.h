#pragma once

#include <lambda_p/core/target.h>

namespace lambda_p
{
	namespace core
	{
		class node;
		class adapter : public lambda_p::core::target
		{
		public:
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments) override;
			boost::shared_ptr <lambda_p::core::node> node;
			boost::shared_ptr <lambda_p::core::target> target;
		};
	}
}

