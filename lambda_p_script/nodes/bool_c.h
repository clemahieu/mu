#pragma once

#include <lambda_p/node.h>

namespace lambda_p_script
{
	namespace nodes
	{
		class bool_c : public lambda_p::node
		{
		public:
			bool_c ();
			bool_c (bool value_a);
			bool value;
		};
	}
}
