#include "node.h"

lambda_p_llvm::value::node::node (llvm::Value * value_a)
	: value_m (value_a)
{
}

llvm::Value * lambda_p_llvm::value::node::value ()
{
	return value_m;
}