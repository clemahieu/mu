#pragma once

#include <core/node.h>

#include <llvm/ADT/APInt.h>

namespace lambda_p_llvm
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

