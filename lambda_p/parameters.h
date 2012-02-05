#pragma once

#include <lambda_p/node.h>

namespace lambda_p
{
	class parameters : public lambda_p::node
	{
	public:
		void operator () (lambda_p::visitor * visitor_a) override;
	};
}

