#include "node.h"

#include <llvm/Argument.h>

lambda_p_llvm::argument::node::node (llvm::Argument * argument_a)
	: lambda_p_llvm::value::node (argument_a)
{
}

llvm::Argument * lambda_p_llvm::argument::node::argument ()
{
	auto result (llvm::cast <llvm::Argument> (value_m));
	return result;
}