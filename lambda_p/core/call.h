#pragma once

#include <lambda_p/core/target.h>

#include <boost/function.hpp>

namespace lambda_p
{
	namespace errors
	{
		class error;
	}
	namespace core
	{
		class call : public lambda_p::core::target
		{
		public:
			call (boost::shared_ptr <lambda_p::core::target> target_a, boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors_a);
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments) override;
			boost::shared_ptr <lambda_p::core::target> target;
			boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors;
		};
	}
}

