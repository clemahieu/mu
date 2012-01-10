#pragma once

#include <lambda_p/node.h>

namespace lambda_p_script
{
	namespace nodes
	{
		class number : public lambda_p::node
		{
		public:
			number ();
			number (unsigned long long value_a);
			unsigned long long value;
		};
	}
}

