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
				boost::shared_ptr <mu::core::node> operator () (boost::shared_ptr <mu::core::node> node_a) override;
				std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::core::node>> mapping;
			};
		}
	}
}