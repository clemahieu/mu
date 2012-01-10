#pragma once

#include <lambda_p/node.h>

#include <string>

namespace lambda_p_script
{
	namespace nodes
	{
		class data : public lambda_p::node
		{
		public:
			 data (std::wstring string_a);
			 std::wstring string;
		};
	}
}

