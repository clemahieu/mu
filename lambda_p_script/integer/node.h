#pragma once

#include <lambda_p/node.h>

namespace lambda_p_script
{
	namespace integer
	{
		class node : public lambda_p::node
		{
		public:
			node ();
			node (unsigned long long value_a);
			std::wstring debug () override;
			unsigned long long value;
		};
	}
}

