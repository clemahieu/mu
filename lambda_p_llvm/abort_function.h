#pragma once

namespace llvm
{
	class Function;
	class LLVMContext;
}
namespace lambda_p_llvm
{
	class generation_context;
	class abort_function
	{
	public:
		abort_function (llvm::LLVMContext & context_a);
		llvm::Function * abort;
	};
}

