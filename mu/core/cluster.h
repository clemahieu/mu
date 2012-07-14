#pragma once

#include <mu/core/node.h>

#include <map>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class routine;
		class cluster : public mu::core::node
		{
		public:
			void operator () (mu::core::visitor * visitor_a) override;
			std::map <std::wstring, mu::core::routine *> names;
			std::vector <mu::core::routine *> routines;
			std::wstring name () override;
		};
	}
}

