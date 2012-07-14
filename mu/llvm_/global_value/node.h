#pragma once

#include <mu/llvm_/value/node.h>

namespace llvm
{
	class GlobalValue;
}
namespace mu
{
	namespace llvm_
	{
		namespace type
		{
			class node;
		}
		namespace global_value
		{
			class node : public mu::llvm_::value::node
			{
			public:
				node (llvm::GlobalValue * value_a, mu::llvm_::type::node * type_a);
				llvm::GlobalValue * global_value ();
			};
		}
	}
}
