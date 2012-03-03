#pragma once

#include <mu/llvm_/context.node.h>

#include <llvm/LLVMContext.h>

namespace mu
	{
	namespace llvm_
	{
		namespace context
		{
			class value : public mu::llvm_::context::node
			{
			public:
				value ();
				llvm::LLVMContext context_m;
			};
		}
	}
}
