#pragma once

#include <lambda_p_llvm/generation_context.h>

#include <llvm/Function.h>

namespace lambda_p_llvm
{
	class malloc_function
	{
	public:
		malloc_function (::lambda_p_llvm::generation_context context_a);
		~malloc_function (void);
        ::llvm::Function * malloc;
	};
}

