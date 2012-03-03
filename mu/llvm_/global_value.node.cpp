#include <mu/llvm_/global_value.node.h>

#include <llvm/GlobalValue.h>

mu::llvm_::global_value::node::node (llvm::GlobalValue * value_a, boost::shared_ptr <mu::llvm_::type::node> type_a)
	: mu::llvm_::value::node (value_a, type_a)
{
}

llvm::GlobalValue * mu::llvm_::global_value::node::global_value ()
{
	auto result (llvm::cast <llvm::GlobalValue> (value_m));
	return result;
}
