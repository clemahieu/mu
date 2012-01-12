#pragma once

#include <lambda_p/expression.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class call : public lambda_p::expression
	{
	public:
		void operator () (lambda_p::visitor * visitor_a) override;
	};
}

