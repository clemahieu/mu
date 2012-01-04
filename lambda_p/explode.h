#pragma once

#include <lambda_p/expression.h>

namespace lambda_p
{
	namespace errors
	{
		class error_target;
	}
	class explode : public lambda_p::expression
	{
	public:
		explode (std::vector <boost::shared_ptr <lambda_p::node>> items_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a);
		void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & parameters, boost::shared_ptr <lambda_p::target> target_a) override;
		std::vector <boost::shared_ptr <lambda_p::node>> items;
		boost::shared_ptr <lambda_p::errors::error_target> errors;
	};
}

