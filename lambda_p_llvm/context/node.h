#pragma once

#include <core/node.h>

#include <llvm/LLVMContext.h>

namespace lambda_p_llvm
{
	namespace context
	{
		class node : public mu::core::node
		{
		public:
			node (llvm::LLVMContext * context_a);
			llvm::LLVMContext * context;
			std::wstring name () override;
		};
	}
}

