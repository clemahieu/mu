#pragma once

#include <lambda_p/target.h>

namespace lambda_p
{
	namespace errors
	{
		class error_target;
	}
	class collapse : public lambda_p::target
	{
	public:
		collapse (boost::shared_ptr <lambda_p::target> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a);
		void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments) override;
		boost::shared_ptr <lambda_p::target> target;
		boost::shared_ptr <lambda_p::errors::error_target> errors;
	};
}

