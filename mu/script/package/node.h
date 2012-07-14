#pragma once

#include <mu/core/node.h>

#include <map>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace script
	{
		namespace package
		{
			class node : public mu::core::node
			{
			public:
				std::map <std::wstring, mu::core::node *> items;
				std::wstring debug () override;
			};
		}
	}
}
