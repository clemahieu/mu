#include "node.h"

lambda_p_llvm_wrapper::type::node::node (llvm::Type * type_a)
	: type_m (type_a)
{
}

llvm::Type * lambda_p_llvm_wrapper::type::node::type ()
{
	return type_m;
}