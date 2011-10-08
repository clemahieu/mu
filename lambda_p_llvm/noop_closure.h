#pragma once

#include <vector>

#include <lambda_p_llvm/value.h>

namespace llvm
{
	class Function;
	class Value;
}
namespace lambda_p_llvm
{
	class generation_context;
	class noop_closure : public ::lambda_p_llvm::value
	{
	public:
		noop_closure (::lambda_p_llvm::generation_context & context_a, ::llvm::Function * function_a, ::std::vector < ::llvm::Value *> arguments_a);
        ::llvm::Value * operator () ();
		::llvm::Type const * type ();
		::lambda_p_llvm::generation_context & context;
		::llvm::Function * function;
		::std::vector < ::llvm::Value *> arguments;
	};
}

