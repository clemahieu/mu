#pragma once

#include <lambda_p_llvm/value.h>

namespace llvm
{
	class Function;
	class FunctionType;
}
namespace lambda_p_llvm
{
	class function : public ::lambda_p_llvm::value
	{
	public:
		function (::llvm::Function * function_a);
		::llvm::FunctionType const * function_type ();
		::llvm::Type const * type ();
		::llvm::Function * function_m;
	};
}

