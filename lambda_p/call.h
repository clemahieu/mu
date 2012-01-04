#pragma once

#include <lambda_p/target.h>

#include <boost/function.hpp>

namespace lambda_p
{
	namespace errors
	{
		class error_target;
	}
	class call : public lambda_p::target
	{
	public:
		call (boost::shared_ptr <lambda_p::target> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a);
		void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments) override;
		boost::shared_ptr <lambda_p::target> target;
		boost::shared_ptr <lambda_p::errors::error_target> errors;
	};
}

