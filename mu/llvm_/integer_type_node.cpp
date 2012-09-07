#include <mu/llvm_/integer_type_node.h>

#include <llvm/DerivedTypes.h>

mu::llvm_::integer_type::node::node (llvm::IntegerType * type_a):
type_m (type_a)
{
}

llvm::Type * mu::llvm_::integer_type::node::type ()
{
	return integer_type ();
}

llvm::IntegerType * mu::llvm_::integer_type::node::integer_type ()
{
	return type_m;
}