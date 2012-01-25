#include "node.h"

#include <llvm/Support/raw_ostream.h>

lambda_p_llvm::type::node::node (llvm::Type * type_a)
	: type_m (type_a)
{
}

llvm::Type * lambda_p_llvm::type::node::type ()
{
	return type_m;
}