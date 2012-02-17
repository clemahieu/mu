#include "node.h"

#include <llvm/GlobalVariable.h>

lambda_p_llvm::global_variable::node::node (llvm::GlobalVariable * value_a, boost::shared_ptr <lambda_p_llvm::type::node> type_a)
	: lambda_p_llvm::global_value::node (value_a, type_a)
{
}

llvm::GlobalVariable * lambda_p_llvm::global_variable::node::global_variable ()
{
	auto result (llvm::cast <llvm::GlobalVariable> (value_m));
	return result;
}