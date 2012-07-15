#pragma once

#include <mu/core/node.h>

#include <map>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

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
			std::map <std::wstring, mu::core::routine *, std::less <std::wstring>, gc_allocator <std::pair <std::wstring, mu::core::routine *>>> names;
			std::vector <mu::core::routine *, gc_allocator <mu::core::routine *>> routines;
			std::wstring name () override;
		};
	}
}

