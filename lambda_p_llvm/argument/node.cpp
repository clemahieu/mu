#include "node.h"

#include <llvm/Argument.h>

llvm::Argument * lambda_p_llvm::argument::node::argument ()
{
	auto result (llvm::cast <llvm::Argument> (value_m));
	return result;
}