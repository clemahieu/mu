#include "node.h"

#include <llvm/DerivedTypes.h>

lambda_p_llvm::function_pointer_type::node::node (llvm::PointerType * function_type_a, bool multiple_return_a)
	: lambda_p_llvm::pointer_type::node (function_type_a),
	multiple_return (multiple_return_a)
{
	assert (function_type_a->getElementType ()->isFunctionTy ());
	assert (llvm::cast <llvm::FunctionType> (function_type_a->getElementType ()));
}

llvm::PointerType * lambda_p_llvm::function_pointer_type::node::function_type ()
{
	auto result (llvm::cast <llvm::PointerType> (type_m));
	return result;
}