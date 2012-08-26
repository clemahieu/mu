#include <mu/llvm_/constant_node.h>

#include <llvm/Constant.h>

mu::llvm_::constant::node::node (llvm::Constant * constant_a, mu::llvm_::type::node * type_a):
mu::llvm_::value::node (constant_a, type_a)
{
}

llvm::Constant * mu::llvm_::constant::node::constant ()
{
	auto result (llvm::cast <llvm::Constant> (value_m));
	return result;
}