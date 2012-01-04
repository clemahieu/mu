#pragma once

#include <lambda_p/expression.h>

namespace lambda_p
{
	namespace errors
	{
		class error_target;
	}
	class implode : public lambda_p::expression
	{
	public:
		implode (boost::shared_ptr <lambda_p::errors::error_target> errors_a);
		void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & parameters, boost::shared_ptr <lambda_p::target> target_a) override;
		boost::shared_ptr <lambda_p::errors::error_target> errors;
	};
}

