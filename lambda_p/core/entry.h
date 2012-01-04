#pragma once

#include <lambda_p/core/target.h>

namespace lambda_p
{
	namespace errors
	{
		class error_target;
	}
	namespace core
	{
		class fixed;
		class tee;
		class entry : public lambda_p::core::target
		{
		public:
			entry (boost::shared_ptr <lambda_p::errors::error_target> errors_a);
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::node>> & arguments) override;
			std::vector <boost::shared_ptr <lambda_p::core::fixed>> fixed;
			boost::shared_ptr <lambda_p::core::tee> next;
			boost::shared_ptr <lambda_p::errors::error_target> errors;
		};
	}
}

