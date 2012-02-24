#pragma once

#include <core/node.h>

namespace lambda_p_script
{
	namespace bool_c
	{
		class node : public mu::core::node
		{
		public:
			node ();
			node (bool value_a);
			std::wstring debug () override;
			bool value;
		};
	}
}
