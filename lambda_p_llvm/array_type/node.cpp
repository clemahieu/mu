#include "node.h"

#include <llvm/DerivedTypes.h>

lambda_p_llvm::array_type::node::node (llvm::ArrayType * type_a)
	: lambda_p_llvm::type::node (type_a)
{
}

llvm::ArrayType * lambda_p_llvm::array_type::node::array_type ()
{
	auto result (llvm::cast <llvm::ArrayType> (type_m));
	return result;
}