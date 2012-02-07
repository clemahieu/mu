#include "node.h"

#include <llvm/Constant.h>

lambda_p_llvm::constant::node::node (llvm::Constant * constant_a, boost::shared_ptr <lambda_p_llvm::type::node> type_a)
	: lambda_p_llvm::value::node (constant_a, type_a)
{
}

llvm::Constant * lambda_p_llvm::constant::node::constant ()
{
	auto result (llvm::cast <llvm::Constant> (value_m));
	return result;
}