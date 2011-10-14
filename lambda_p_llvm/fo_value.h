#pragma once

#include <lambda_p_llvm/value.h>

namespace lambda_p_llvm
{
	class fo_value : public ::lambda_p_llvm::value
	{
	public:
		fo_value (::llvm::Value * value_a);
        ::llvm::Value * operator () ();
		::llvm::Type const * type ();
		::llvm::Value * value;
	};
}

