#pragma once

#include <lambda_p/node.h>

namespace lambda_p_script
{
	namespace bool_c
	{
		class node : public lambda_p::node
		{
		public:
			node ();
			node (bool value_a);
			std::wstring debug () override;
			bool value;
		};
	}
}
