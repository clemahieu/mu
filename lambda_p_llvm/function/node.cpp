#include "node.h"

#include <llvm/Function.h>

lambda_p_llvm::function::node::node (llvm::Function * function_a)
	: lambda_p_llvm::value::node (function_a)
{
}

llvm::Function * lambda_p_llvm::function::node::function ()
{
	auto result (llvm::cast <llvm::Function> (value_m));
	return result;
}