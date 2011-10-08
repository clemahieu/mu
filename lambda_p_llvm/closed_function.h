#pragma once

#include <lambda_p_llvm/function.h>

namespace lambda_p_llvm
{
	class closed_function : public ::lambda_p_llvm::function
	{
	public:
		closed_function (::llvm::Function * function_a);
	};
}

