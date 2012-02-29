#pragma once

#include <mu/core/node.h>

namespace mu
{
	namespace script
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
}