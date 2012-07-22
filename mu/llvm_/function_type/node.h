#pragma once

#include <mu/llvm_/type/node.h>

#include <vector>

#include <gc_allocator.h>

namespace llvm
{
	class FunctionType;
}
namespace mu
{
	namespace llvm_
	{
		namespace context
		{
			class node;
		}
		namespace function_type
		{
			class node : public mu::llvm_::type::node
			{
			public:
				node (mu::llvm_::context::node * context_a, llvm::FunctionType * function_type_a);
				node (mu::llvm_::context::node * context_a, std::vector <mu::llvm_::type::node *, gc_allocator <mu::llvm_::type::node *>> parameters_a, mu::llvm_::type::node * output_a);
				llvm::Type * type () override;
				llvm::FunctionType * function_type ();
				mu::llvm_::context::node * context;
				std::vector <mu::llvm_::type::node *, gc_allocator <mu::llvm_::type::node *>> parameters;
				mu::llvm_::type::node * output;
			};
		}
	}
}
