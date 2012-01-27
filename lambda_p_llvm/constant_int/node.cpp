#include "node.h"

#include <llvm/Constants.h>

lambda_p_llvm::constant_int::node::node (llvm::ConstantInt * constant_int_a)
	: lambda_p_llvm::constant::node (constant_int_a)
{
}

llvm::ConstantInt * lambda_p_llvm::constant_int::node::constant_int ()
{
	auto result (llvm::cast <llvm::ConstantInt> (value_m));
	return result;
}