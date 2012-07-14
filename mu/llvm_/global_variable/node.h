#pragma once

#include <mu/llvm_/global_value/node.h>

namespace llvm
{
	class GlobalVariable;
}
namespace mu
{
	namespace llvm_
	{
		namespace global_variable
		{
			class node : public mu::llvm_::global_value::node
			{
			public:
				node (llvm::GlobalVariable * value_a, mu::llvm_::type::node * type_a);
				llvm::GlobalVariable * global_variable ();
			};
		}
	}
}
