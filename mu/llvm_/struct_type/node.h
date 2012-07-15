#pragma once

#include <mu/llvm_/type/node.h>

#include <vector>

#include <boost/shared_ptr.hpp>

#include <gc_allocator.h>

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
				node (mu::llvm_::context::node * context_a, std::vector <mu::llvm_::type::node *, gc_allocator <mu::llvm_::type::node *>> elements_a);
				llvm::Type * type () override;
				llvm::StructType * struct_type ();
				mu::llvm_::context::node * context;
				std::vector <mu::llvm_::type::node *, gc_allocator <mu::llvm_::type::node *>> elements;
			};
		}
	}
}
