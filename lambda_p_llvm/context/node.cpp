#include "node.h"

lambda_p_llvm::context::node::node (llvm::LLVMContext * context_a)
	: context (context_a)
{
}

std::wstring lambda_p_llvm::context::node::name ()
{
	return std::wstring (L"lambda_p_llvm::context::node");
}