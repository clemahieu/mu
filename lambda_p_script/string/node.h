#pragma once

#include <core/node.h>

#include <string>

namespace lambda_p_script
{
	namespace string
	{
		class node : public mu::core::node
		{
		public:
			 node (std::wstring string_a);
			 std::wstring debug () override;
			 std::wstring string;
		};
	}
}

