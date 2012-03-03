#pragma once

#include <mu/core/node.h>

#include <llvm/ADT/APInt.h>

namespace mu
{
	namespace llvm_
	{
		namespace apint
		{
			class node : public mu::core::node
			{
			public:
				node (llvm::APInt * value_a);
				llvm::APInt * value;
			};
		}
	}
}
