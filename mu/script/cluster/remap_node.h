#pragma once

#include <mu/script/cluster/remap.h>

#include <map>

namespace mu
{
	namespace script
	{
		namespace cluster
		{
			class remap_node : public mu::script::cluster::remap
			{
			public:
				mu::core::node * operator () (mu::core::node * node_a) override;
				std::map <mu::core::node *, mu::core::node *> mapping;
			};
		}
	}
}