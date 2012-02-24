#include "node.h"

mu::llvm_::predicate::node::node (llvm::CmpInst::Predicate value_a)
	: value (value_a)
{
}