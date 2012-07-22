#pragma once

#include <mu/core/node.h>

#include <map>
#include <vector>

namespace mu
{
	namespace script
	{
		namespace cluster
		{
			class node;
		}
	}
	namespace llvm_
	{
		namespace function
		{
			class node;
		}
		namespace cluster
		{
			class node : public mu::core::node
			{
			public:
				mu::string name () override;
				std::map <mu::string, mu::llvm_::function::node *> names;
				std::vector <mu::llvm_::function::node *> routines;
			};
		}
	}
}

