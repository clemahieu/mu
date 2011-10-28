#pragma once

#include <lambda_p/binder/node.h>

#include <llvm/LLVMContext.h>

namespace lambda_p_llvm
{
	class context : public lambda_p::binder::node
	{
	public:
		context (void);
		~context (void);
		llvm::LLVMContext context_m;
	};
}

