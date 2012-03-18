#pragma once

#include <mu/core/node.h>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace script_runtime
	{
        class context;
		class operation : public mu::core::node
		{
		public:
			virtual bool operator () (mu::script_runtime::context & context_a) = 0;
		};
	}
}
