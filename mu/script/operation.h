#pragma once

#include <mu/core/node.h>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace script
	{
        class context;
		class operation : public mu::core::node
		{
		public:
			virtual void operator () (mu::script::context & context_a) = 0;
		};
	}
}
