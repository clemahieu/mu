#include "node.h"

#include <llvm/Constants.h>

mu::llvm_::constant_int::node::node (llvm::ConstantInt * constant_int_a, mu::llvm_::type::node * type_a)
	: mu::llvm_::constant::node (constant_int_a, type_a)
{
}

llvm::ConstantInt * mu::llvm_::constant_int::node::constant_int ()
{
	auto result (llvm::cast <llvm::ConstantInt> (value_m));
	return result;
}

mu::string mu::llvm_::constant_int::node::name ()
{
	return mu::string (U"mu::llvm_::constant_int::node");
}