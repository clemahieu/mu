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
				node (mu::string string_a);
				mu::string name () override;
				mu::string debug () override;
				mu::string string;
			};
		}
	}
}
