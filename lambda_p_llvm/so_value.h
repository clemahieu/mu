#pragma once

#include <lambda_p_llvm/value.h>

namespace lambda_p_llvm
{
	class so_value : public ::lambda_p_llvm::value
	{
	public:
		so_value (::llvm::Function * function_a);
		::llvm::Type const * type ();
		::llvm::Function * function;
	};
}

