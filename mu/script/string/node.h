#pragma once

#include <mu/core/node.h>

#include <string>

namespace mu
{
	namespace script
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
}
