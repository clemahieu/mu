#pragma once

#include <lambda_p/core/node.h>

namespace lambda_p_kernel
{
	namespace nodes
	{
		class bool_c : public lambda_p::core::node
		{
		public:
			bool_c ();
			bool_c (bool value_a);
			bool value;
		};
	}
}

