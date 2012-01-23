#pragma once

#include <lambda_p_llvm/value/node.h>

namespace lambda_p_llvm
{
	namespace function_pointer
	{
		class node : public lambda_p_llvm::value::node
		{
		public:
			node (llvm::Value * value_a, bool multiple_return_a);
			bool multiple_return;
		};
	}
}

