#pragma once

#include <lambda_p/binder/node_instance.h>

namespace llvm
{
	class Function;
}
namespace lambda_p_llvm
{
	class function_binder : public ::lambda_p::binder::node_instance
	{
	public:
		function_binder (::llvm::Function * function_a);
		::llvm::Function * function;
	};
}

