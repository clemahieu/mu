#pragma once

#include <lambda_p/core/expression.h>

namespace lambda_p
{
	namespace errors
	{
		class error_target;
	}
	namespace core
	{
		class implode : public lambda_p::core::expression
		{
		public:
			implode (boost::shared_ptr <lambda_p::errors::error_target> errors_a);
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::node>> & parameters, boost::shared_ptr <lambda_p::core::target> target_a) override;
			boost::shared_ptr <lambda_p::errors::error_target> errors;
		};
	}
}

