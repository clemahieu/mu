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
				mu::string name () override;
				mu::string debug () override;
			};
		}
	}
}
