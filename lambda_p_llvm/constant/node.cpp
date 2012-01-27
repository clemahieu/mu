#include "node.h"

#include <llvm/Constant.h>

lambda_p_llvm::constant::node::node (llvm::Constant * constant_a)
	: lambda_p_llvm::value::node (constant_a)
{
}

llvm::Constant * lambda_p_llvm::constant::node::constant ()
{
	auto result (llvm::cast <llvm::Constant> (value_m));
	return result;
}