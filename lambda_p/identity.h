#pragma once

#include <lambda_p/expression.h>

namespace lambda_p
{
	class identity : public lambda_p::expression
	{
	public:
		void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & parameters, boost::shared_ptr <lambda_p::target> target_a) override;
	};
}

