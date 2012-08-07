#include <mu/llvm_/instructions/urem.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/script/check.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::llvm_::instructions::urem::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::llvm_::value::node, mu::llvm_::value::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::value::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::value::node *> (context_a.parameters (1)));
		bool one_int (one->value ()->getType ()->isIntegerTy ());
		bool two_int (two->value ()->getType ()->isIntegerTy ());
		if (one_int && two_int)
		{
			size_t one_bits (one->value ()->getType ()->getPrimitiveSizeInBits ());
			size_t two_bits (two->value ()->getType ()->getPrimitiveSizeInBits ());
			if (one_bits == two_bits)
			{
				auto instruction (llvm::BinaryOperator::CreateURem (one->value (), two->value ()));
				context_a.push (new (GC) mu::llvm_::instruction::node (instruction, one->type));
			}
			else
			{
				mu::stringstream message;
				message << L"Bit widths don't match: ";
				message << one_bits;
				message << L" ";
				message << two_bits;
				context_a.errors (message.str ());
				valid = false;
			}
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