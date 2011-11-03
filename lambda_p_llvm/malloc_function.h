#pragma once

namespace llvm
{
    class Function;
	class LLVMContext;
	class Type;
}
namespace lambda_p_llvm
{
	class generation_context;
	class malloc_function
	{
	public:
		malloc_function (llvm::LLVMContext & context_a, llvm::Type const * size_t_type);
        llvm::Function * malloc;
	};
}

