#include "node.h"

#include <llvm/Instruction.h>

mu::llvm_::instruction::node::node (llvm::Instruction * instruction_a, mu::llvm_::type::node * type_a)
	: mu::llvm_::value::node (instruction_a, type_a)
{
}

llvm::Instruction * mu::llvm_::instruction::node::instruction ()
{
	auto result (llvm::cast <llvm::Instruction> (value_m));
	return result;
}