#pragma once

#include <mu/core/node.h>

namespace mu
{
	namespace script
	{
		namespace integer
		{
			class node : public mu::core::node
			{
			public:
				node ();
				node (unsigned long long value_a);
				std::wstring name () override;
				std::wstring debug () override;
				unsigned long long value;
			};
		}
	}
}
