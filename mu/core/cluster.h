#pragma once

#include <mu/core/node.h>

#include <map>
#include <string>
#include <vector>

#include <gc_allocator.h>

namespace mu
{
	namespace core
	{
		class routine;
		class cluster : public mu::core::node
		{
		public:
			void operator () (mu::core::visitor * visitor_a) override;
			mu::map <mu::string, mu::core::routine *> names;
			mu::vector <mu::core::routine *> routines;
            mu::string name () override;
		};
	}
}

