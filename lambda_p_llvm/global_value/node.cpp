#include "node.h"

#include <llvm/GlobalValue.h>

lambda_p_llvm::global_value::node::node (llvm::GlobalValue * value_a, boost::shared_ptr <lambda_p_llvm::type::node> type_a)
	: lambda_p_llvm::value::node (value_a, type_a)
{
}

llvm::GlobalValue * lambda_p_llvm::global_value::node::global_value ()
{
	auto result (llvm::cast <llvm::GlobalValue> (value_m));
	return result;
}