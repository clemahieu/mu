#pragma once

#include <lambda_p/node.h>

#include <string>

namespace lambda_p_script
{
	namespace string
	{
		class node : public lambda_p::node
		{
		public:
			 node (std::wstring string_a);
			 std::wstring debug () override;
			 std::wstring string;
		};
	}
}

