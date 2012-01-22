#pragma once

#include <lambda_p_llvm/value/node.h>

namespace llvm
{
	class Function;
}
namespace lambda_p_llvm
{
	namespace function
	{
		class node : public lambda_p_llvm::value::node
		{
		public:
			node (llvm::Function * function_a, bool multiple_return_a);
			llvm::Function * function ();
			bool multiple_return;
		};
	}
}

