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
				mu::core::node * operator () (mu::core::node * node_a) override;
				std::map <mu::core::routine *, mu::llvm_::function::node *> mapping;
			};
		}
	}
}