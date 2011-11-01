#pragma once

namespace llvm
{
    class Function;
}
namespace lambda_p_llvm
{
	class generation_context;
	class malloc_function
	{
	public:
		malloc_function (lambda_p_llvm::generation_context & context_a);
        llvm::Function * malloc;
	};
}

