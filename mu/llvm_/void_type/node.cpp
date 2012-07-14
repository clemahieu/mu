#include "node.h"

#include <mu/llvm_/context/node.h>

#include <llvm/DerivedTypes.h>

mu::llvm_::void_type::node::node (mu::llvm_::context::node * context_a)
	: type_m (llvm::Type::getVoidTy (*context_a->context))
{
}

llvm::Type * mu::llvm_::void_type::node::type ()
{
	return type_m;
}