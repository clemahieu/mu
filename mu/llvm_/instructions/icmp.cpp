#include <mu/llvm_/instructions/icmp.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/llvm_/predicate/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/script/check.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::llvm_::instructions::icmp::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::llvm_::predicate::node, mu::llvm_::value::node, mu::llvm_::value::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::predicate::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::value::node *> (context_a.parameters (1)));
		auto three (static_cast <mu::llvm_::value::node *> (context_a.parameters (2)));
		bool two_int (two->value ()->getType ()->isIntegerTy ());
		bool three_int (three->value ()->getType ()->isIntegerTy ());
		if (two_int && three_int)
		{
			size_t one_bits (two->value ()->getType ()->getPrimitiveSizeInBits ());
			size_t two_bits (three->value ()->getType ()->getPrimitiveSizeInBits ());
			if (one_bits == two_bits)
			{
				auto instruction (new llvm::ICmpInst (one->value, two->value (), three->value ()));
				context_a.push (new (GC) mu::llvm_::instruction::node (instruction, new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (two->value ()->getContext ()))));
			}
			else
			{
				mu::stringstream message;
				message << L"Bit widths don't match: ";
				message << one_bits;
				message << L" ";
				message << two_bits;
				context_a.errors (message.str ());
			}
		}
		else
		{
			mu::stringstream message;
			message << L"Arguments are not integers: ";
			message << two_int;
			message << L" ";
			message << three_int;
			context_a.errors (message.str ());
		}
	}
	return result;
}

mu::string mu::llvm_::instructions::icmp::name ()
{
	return mu::string (U"mu::llvm_::instructions::icmp");
}