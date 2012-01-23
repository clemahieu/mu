#include "node.h"

#include <llvm/DerivedTypes.h>

lambda_p_llvm::pointer_type::node::node (llvm::PointerType * type_a)
	: lambda_p_llvm::type::node (type_a)
{
}

llvm::PointerType * lambda_p_llvm::pointer_type::node::pointer_type ()
{
	auto result (llvm::dyn_cast <llvm::PointerType> (type_m));
	return result;
}