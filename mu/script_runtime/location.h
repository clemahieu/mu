#pragma once

#include <mu/core/node.h>

namespace mu
{
	namespace script_runtime
	{
		class location : public mu::core::node
		{
		public:
			location (size_t position_a);
			size_t position;
		};
	}
}