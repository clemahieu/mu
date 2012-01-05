#pragma once

#include <lambda_p/node.h>

namespace lambda_p_script
{
	namespace nodes
	{
		class parameters : public lambda_p::node
		{
		public:
			parameters (size_t count_a);
			size_t count;
		};
	}
}

