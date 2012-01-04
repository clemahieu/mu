#pragma once

#include <lambda_p/target.h>

namespace lambda_p
{
	namespace errors
	{
		class error_target;
	}
	class fixed;
	class tee;
	class entry : public lambda_p::target
	{
	public:
		entry (boost::shared_ptr <lambda_p::errors::error_target> errors_a);
		void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments) override;
		std::vector <boost::shared_ptr <lambda_p::fixed>> fixed;
		boost::shared_ptr <lambda_p::tee> next;
		boost::shared_ptr <lambda_p::errors::error_target> errors;
	};
}

