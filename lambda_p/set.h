#pragma once

#include <lambda_p/node.h>

namespace lambda_p
{
	class set : public lambda_p::node
	{
	public:
		set ();
		void operator () (lambda_p::visitor * visitor_a) override;
		size_t count;
	};
}

