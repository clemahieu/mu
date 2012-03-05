#include "node.h"

#include <llvm/GlobalVariable.h>

mu::llvm_::global_variable::node::node (llvm::GlobalVariable * value_a, boost::shared_ptr <mu::llvm_::type::node> type_a)
	: mu::llvm_::global_value::node (value_a, type_a)
{
}

llvm::GlobalVariable * mu::llvm_::global_variable::node::global_variable ()
{
	auto result (llvm::cast <llvm::GlobalVariable> (value_m));
	return result;
}