#include "node.h"

lambda_p_llvm::linkage_types::node::node (llvm::GlobalValue::LinkageTypes type_a)
	: type (type_a)
{
}