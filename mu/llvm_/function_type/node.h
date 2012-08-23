#pragma once

#include <mu/llvm_/type/node.h>

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
				node (mu::llvm_::context::node * context_a, mu::vector <mu::llvm_::type::node *> parameters_a, mu::llvm_::type::node * output_a);
				node (mu::llvm_::context::node * context_a, mu::vector <mu::llvm_::type::node *> parameters_a, mu::vector <mu::llvm_::type::node *> outputs_a);
				llvm::Type * type () override;
				llvm::FunctionType * function_type ();
				mu::llvm_::context::node * context;
				mu::vector <mu::llvm_::type::node *> parameters;
				mu::llvm_::type::node * output;
			};
		}
	}
}
