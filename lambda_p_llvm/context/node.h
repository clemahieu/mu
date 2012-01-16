#pragma once

#include <lambda_p/node.h>

#include <llvm/LLVMContext.h>

namespace lambda_p_llvm
{
	namespace context
	{
		class node : public lambda_p::node
		{
		public:
			llvm::LLVMContext context;
			std::wstring name () override;
		};
	}
}

