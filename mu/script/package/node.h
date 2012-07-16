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
				std::map <mu::string, mu::core::node *> items;
				mu::string debug () override;
			};
		}
	}
}
