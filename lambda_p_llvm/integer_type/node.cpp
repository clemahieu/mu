#include "node.h"

#include <llvm/DerivedTypes.h>

lambda_p_llvm::integer_type::node::node (llvm::IntegerType * type_a)
	: lambda_p_llvm::type::node (type_a)
{
}

llvm::IntegerType * lambda_p_llvm::integer_type::node::integer_type ()
{
	auto result (llvm::cast <llvm::IntegerType> (type_m));
	return result;
}