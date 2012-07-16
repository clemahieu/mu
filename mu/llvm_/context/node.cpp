#include "node.h"

mu::llvm_::context::node::node (llvm::LLVMContext * context_a)
	: context (context_a)
{
}

mu::string mu::llvm_::context::node::name ()
{
	return mu::string (U"mu::llvm_::context::node");
}