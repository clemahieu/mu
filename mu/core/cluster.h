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
			std::map <mu::string, mu::core::routine *, std::less <mu::string>, gc_allocator <std::pair <mu::string, mu::core::routine *>>> names;
			std::vector <mu::core::routine *, gc_allocator <mu::core::routine *>> routines;
            mu::string name () override;
		};
	}
}

