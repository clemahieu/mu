#pragma once

#include <lambda_p/core/node.h>

#include <boost/function.hpp>

namespace lambda_p
{
	namespace errors
	{
		class error;
	}
	namespace core
	{
		class implode : public lambda_p::core::node
		{
		public:
			implode (boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors_a);
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> parameters, boost::shared_ptr <lambda_p::core::target> target_a) override;
			boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors;
		};
	}
}

