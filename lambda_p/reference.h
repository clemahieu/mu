#pragma once

#include <lambda_p/node.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class expression;
	class reference : public lambda_p::node
	{
	public:
		boost::shared_ptr <lambda_p::expression> expression;
		size_t index;
	};
}
