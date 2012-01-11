#pragma once

#include <lambda_p/node.h>

#include <string>

namespace lambda_p_script
{
	namespace data
	{
		class node : public lambda_p::node
		{
		public:
			 node (std::wstring string_a);
			 std::wstring string;
		};
	}
}

