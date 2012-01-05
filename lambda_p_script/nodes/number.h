#pragma once

#include <lambda_p/core/node.h>

namespace lambda_p_kernel
{
	namespace nodes
	{
		class number : public lambda_p::core::node
		{
		public:
			number (long long int value_a);
			long long int value;
		};
	}
}

