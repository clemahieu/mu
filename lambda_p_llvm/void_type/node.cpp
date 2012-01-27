#include "node.h"

lambda_p_llvm::void_type::node::node (llvm::Type * type_a)
	: lambda_p_llvm::type::node (type_a)
{
	assert (type_a->isVoidTy ());
}