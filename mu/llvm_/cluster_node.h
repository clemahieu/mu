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
        namespace module
        {
            class node;
        }
		namespace cluster
		{
			class node : public mu::core::node
			{
			public:
                node (mu::llvm_::module::node * module_a);
				mu::string name () override;
                mu::llvm_::module::node * module;
				mu::map <mu::string, mu::llvm_::function::node *> routines;
			};
		}
	}
}

