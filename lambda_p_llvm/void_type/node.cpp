#include "node.h"

#include <lambda_p_llvm/context/node.h>

#include <llvm/DerivedTypes.h>

lambda_p_llvm::void_type::node::node (boost::shared_ptr <lambda_p_llvm::context::node> context_a)
	: type_m (llvm::Type::getVoidTy (context_a->context))
{
}

llvm::Type * lambda_p_llvm::void_type::node::type ()
{
	return type_m;
}