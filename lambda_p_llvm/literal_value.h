#pragma once

#include <lambda_p_llvm/value.h>

namespace lambda_p_llvm
{
	class literal_value : public ::lambda_p_llvm::value
	{
	public:
		literal_value (::llvm::Value * value_a);
        ::llvm::Value * operator () ();
		::llvm::Type const * type ();
		::llvm::Value * value;
	};
}

