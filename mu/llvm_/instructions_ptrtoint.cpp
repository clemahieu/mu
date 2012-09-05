#include <mu/llvm_/instructions_ptrtoint.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/instruction_node.h>
#include <mu/llvm_/type_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::llvm_::instructions::ptrtoint::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::llvm_::value::node, mu::llvm_::type::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::value::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::type::node *> (context_a.parameters (1)));
		bool one_int (one->value ()->getType ()->isPointerTy ());
		bool two_int (two->type ()->isIntegerTy ());
		if (one_int && two_int)
		{
			auto instruction (new llvm::PtrToIntInst (one->value (), two->type ()));
			context_a.push (new (GC) mu::llvm_::instruction::node (instruction, two));
		}
		else
		{
			mu::stringstream message;
			message << L"Arguments are not integers: ";
			message << one_int;
			message << L" ";
			message << two_int;
			context_a.errors (message.str ());
			valid = false;
		}
	}
	return valid;
}