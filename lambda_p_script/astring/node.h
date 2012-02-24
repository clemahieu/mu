#pragma once

#include <core/node.h>

namespace lambda_p_script
{
	namespace astring
	{
		class node : public mu::core::node
		{
		public:
			node ();
			node (std::string string_a);
			std::string string;
			std::wstring name () override;
			std::wstring debug () override;
		};
	}
}

