#pragma once

#include <lambda_p/node.h>

namespace llvm
{
	class Function;
}
namespace lambda_p_llvm
{
	namespace function
	{
		class node : public lambda_p::node
		{
		public:
			node (llvm::Function * function_a);
			llvm::Function * function;
		};
	}
}

