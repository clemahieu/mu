#pragma once

#include <mu/llvm_/struct_type/node.h>

#include <gc_allocator.h>

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
				node (mu::llvm_::context::node * context_a, std::vector <mu::llvm_::type::node *, gc_allocator <mu::llvm_::type::node *>> elements_a);
				node (mu::llvm_::struct_type::node * struct_a);
			};
		}
	}
}
