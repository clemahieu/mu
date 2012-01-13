#pragma once

#include <lambda_p/expression.h>

namespace lambda_p
{
	class call : public lambda_p::expression
	{
	public:
		void operator () (lambda_p::visitor * visitor_a) override;
	};
}

