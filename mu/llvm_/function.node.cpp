#include <mu/llvm_/function.node.h>

#include <llvm/Function.h>

mu::llvm_::function::node::node (llvm::Function * function_a, boost::shared_ptr <mu::llvm_::type::node> type_a)
	: mu::llvm_::global_value::node (function_a, type_a)
{
}

llvm::Function * mu::llvm_::function::node::function ()
{
	auto result (llvm::cast <llvm::Function> (value_m));
	return result;
}
