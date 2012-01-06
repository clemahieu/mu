#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class expression;
	class routine
	{
	public:
		routine (boost::shared_ptr <lambda_p::expression> expression_a);
		boost::shared_ptr <lambda_p::expression> expression;
	};
}

