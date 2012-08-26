#pragma once

#include <mu/core/node.h>

namespace mu
{
	namespace script
	{
		namespace runtime
		{
			class routine;
		}
		namespace cluster
		{
			class node : public mu::core::node
			{
			public:
				mu::map <mu::string, mu::script::runtime::routine *> names;
				mu::vector <mu::script::runtime::routine *> routines;
			};
		}
	}
}
