#pragma once

#include <mu/llvm_/global_value_node.h>

namespace llvm
{
	class Function;
}
namespace mu
{
	namespace llvm_
	{
		namespace function
		{
			class node : public mu::llvm_::global_value::node
			{
			public:
				node (llvm::Function * function_a, mu::llvm_::type::node * type_a);
				llvm::Function * function ();
			};
		}
	}
}
