#pragma once

#include <mu/llvm_/value/node.h>

namespace llvm
{
	class Constant;
}
namespace mu
{
	namespace llvm_
	{
		namespace constant
		{
			class node : public mu::llvm_::value::node
			{
			public:
				node (llvm::Constant * constant_a, mu::llvm_::type::node * type_a);
				llvm::Constant * constant ();
			};
		}
	}
}
