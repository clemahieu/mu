#pragma once

#include <lambda_p/core/node.h>

namespace lambda_p
{
	namespace core
	{
		class identity : public lambda_p::core::node
		{
		public:
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> parameters, boost::shared_ptr <lambda_p::core::target> target_a) override;
		};
	}
}

