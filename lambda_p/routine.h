#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class node;
	class expression;
	class routine
	{
	public:
		routine ();
		boost::shared_ptr <lambda_p::expression> parameters;
		boost::shared_ptr <lambda_p::expression> body;
	};
}

