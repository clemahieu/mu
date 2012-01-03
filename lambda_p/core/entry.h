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
		class fixed;
		class tee;
		class entry : public lambda_p::core::target
		{
		public:
			entry (boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors_a);
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> & arguments) override;
			std::vector <boost::shared_ptr <lambda_p::core::fixed>> fixed;
			boost::shared_ptr <lambda_p::core::tee> next;
			boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors;
		};
	}
}

