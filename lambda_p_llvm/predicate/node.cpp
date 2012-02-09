#include "node.h"

lambda_p_llvm::predicate::node::node (llvm::CmpInst::Predicate value_a)
	: value (value_a)
{
}