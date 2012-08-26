#pragma once

#include <mu/llvm_/type_node.h>

namespace llvm
{
	class StructType;
}
namespace mu
{
	namespace llvm_
	{
		namespace context
		{
			class node;
		}
		namespace struct_type
		{
			class node : public mu::llvm_::type::node
			{
			public:
				node (mu::llvm_::context::node * context_a, llvm::StructType * struct_type_a);
				node (mu::llvm_::context::node * context_a);
				node (mu::llvm_::context::node * context_a, mu::vector <mu::llvm_::type::node *> elements_a);
				llvm::Type * type () override;
				llvm::StructType * struct_type ();
				mu::llvm_::context::node * context;
				mu::vector <mu::llvm_::type::node *> elements;
			};
		}
	}
}
