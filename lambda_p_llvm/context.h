#pragma once

#include <lambda_p/binder/node_instance.h>

#include <llvm/LLVMContext.h>

namespace lambda_p_llvm
{
	class context : public ::lambda_p::binder::node_instance
	{
	public:
		context (void);
		~context (void);
		::llvm::LLVMContext context_m;
	};
}

