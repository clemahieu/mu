#pragma once

#include <mu/core/node.h>

#include <llvm/LLVMContext.h>

namespace mu
{
	namespace llvm_
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
}
