#pragma once

#include <mu/core/node.h>
#include <mu/io/debugging/context.h>

#include <vector>

#include <gc_allocator.h>

namespace mu
{
	namespace core
	{
		class expression : public mu::core::node
		{
		public:
			std::vector <mu::core::node *, gc_allocator <mu::core::node *>> dependencies;
			void operator () (mu::core::visitor * visitor_a) override;
		};
	}
}

