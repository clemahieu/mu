#include <mu/llvm_/context.node.h>

mu::llvm_::context::node::node (llvm::LLVMContext * context_a)
	: context (context_a)
{
}

std::wstring mu::llvm_::context::node::name ()
{
	return std::wstring (L"mu::llvm_::context::node");
}
