#pragma once

#include <mu/script/cluster/remap.h>

#include <map>

namespace mu
{
	namespace llvm_
	{
		namespace function
		{
			class node;
		}
		namespace cluster
		{
			class remap : public mu::script::cluster::remap
			{
			public:
				boost::shared_ptr <mu::core::node> operator () (boost::shared_ptr <mu::core::node> node_a) override;
				std::map <boost::shared_ptr <mu::core::routine>, boost::shared_ptr <mu::llvm_::function::node>> mapping;
			};
		}
	}
}