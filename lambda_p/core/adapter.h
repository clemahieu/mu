#pragma once

#include <lambda_p/core/input.h>

namespace lambda_p
{
	namespace core
	{
		class connection;
		class adapter : public lambda_p::core::input
		{
		public:
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments) override;
			boost::shared_ptr <lambda_p::core::connection> connection;
			boost::shared_ptr <lambda_p::core::input> target;
		};
	}
}

