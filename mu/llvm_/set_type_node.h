#pragma once

#include <mu/llvm_/struct_type_node.h>

namespace mu
{
	namespace llvm_
	{
		namespace set_type
		{
			class node : public mu::llvm_::struct_type::node
			{
			public:			
				node (mu::llvm_::context::node * context_a);
				node (mu::llvm_::context::node * context_a, mu::vector <mu::llvm_::type::node *> elements_a);
				node (mu::llvm_::struct_type::node * struct_a);
			};
		}
	}
}
