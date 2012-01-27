#include "node.h"

#include <llvm/DerivedTypes.h>

lambda_p_llvm::struct_type::node::node (llvm::StructType * type_a)
	: lambda_p_llvm::type::node (type_a)
{
}

llvm::StructType * lambda_p_llvm::struct_type::node::structure_type ()
{
	auto result (llvm::cast <llvm::StructType> (type_m));
	return result;
}