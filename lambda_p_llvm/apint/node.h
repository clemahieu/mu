#pragma once

#include <lambda_p/node.h>

#include <llvm/ADT/APInt.h>

namespace lambda_p_llvm
{
	namespace apint
	{
		class node : public lambda_p::node
		{
		public:
			node (llvm::APInt * value_a);
			llvm::APInt * value;
		};
	}
}

