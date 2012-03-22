#pragma once

#include <mu/core/node.h>

#include <map>
#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace script
	{
		class operation;
		namespace cluster
		{
			class node : public mu::core::node
			{
			public:
				std::map <std::wstring, boost::shared_ptr <mu::script::operation>> names;
				std::vector <boost::shared_ptr <mu::script::operation>> routines;
			};
		}
	}
}
