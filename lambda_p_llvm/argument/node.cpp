#include "node.h"

#include <llvm/Argument.h>

lambda_p_llvm::argument::node::node (llvm::Argument * argument_a, boost::shared_ptr <lambda_p_llvm::type::node> type_a)
	: lambda_p_llvm::value::node (argument_a, type_a)
{
}

llvm::Argument * lambda_p_llvm::argument::node::argument ()
{
	auto result (llvm::cast <llvm::Argument> (value_m));
	return result;
}