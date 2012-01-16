#pragma once

#include <lambda_p/node.h>

namespace lambda_p_script
{
	namespace astring
	{
		class node : public lambda_p::node
		{
		public:
			node (std::string string_a);
			std::string string;
			std::wstring name () override;
			std::wstring debug () override;
		};
	}
}

