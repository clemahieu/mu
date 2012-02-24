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
			std::map <std::wstring, boost::shared_ptr <mu::core::routine>> names;
			std::vector <boost::shared_ptr <mu::core::routine>> routines;
			std::wstring name () override;
		};
	}
}

