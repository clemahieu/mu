#pragma once

#include <lambda_p_llvm/context/node.h>

#include <llvm/LLVMContext.h>

namespace lambda_p_llvm
{
	namespace context
	{
		class value : public lambda_p_llvm::context::node
		{
		public:
			value ();
			llvm::LLVMContext context_m;
		};
	}
}

