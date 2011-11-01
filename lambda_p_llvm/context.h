#pragma once

#include <lambda_p/binder/node.h>

#include <llvm/LLVMContext.h>

namespace lambda_p_llvm
{
	class context : public lambda_p::binder::node
	{
	public:
		llvm::LLVMContext context_m;
	};
}

