#include <mu/llvm_/instructions/bitcast.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/llvm_/type/node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::llvm_::instructions::bitcast::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::llvm_::value::node, mu::llvm_::type::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::value::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::type::node *> (context_a.parameters (1)));
		auto instruction (new llvm::BitCastInst (one->value (), two->type ()));
		context_a.push (new (GC) mu::llvm_::instruction::node (instruction, two));
	}
	return result;
}