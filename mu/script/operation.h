#pragma once

#include <mu/core/node.h>

namespace mu
{
	namespace script
	{
        class context;
		class operation : public mu::core::node
		{
		public:
			virtual bool operator () (mu::script::context & context_a) = 0;
		};
	}
}
