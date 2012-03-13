#pragma once

#include <mu/core/context.h>
#include <mu/io/debugging/node.h>

#include <vector>

namespace mu
{
	namespace io
	{
		namespace debugging
		{
			class routine;
			class node;
			class expression : public mu::io::debugging::node
			{
			public:
				std::vector <mu::io::debugging::node *> dependencies;
			};
		}
	}
}