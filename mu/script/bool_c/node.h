#pragma once

#include <mu/core/node.h>

namespace mu
{
	namespace script
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
}