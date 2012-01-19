#include "type_set.h"

#include <llvm/DerivedTypes.h>

lambda_p_llvm::type::type_set::type_set (llvm::StructType * type_a)
	: node (type_a)
{
}

llvm::StructType * lambda_p_llvm::type::type_set::struct_type ()
{
	auto result (llvm::cast <llvm::StructType> (type_m));
	return result;
}