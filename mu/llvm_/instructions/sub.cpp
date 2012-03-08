#include "sub.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/instruction/node.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::instructions::sub::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::value::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::value::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			bool one_int (one->value ()->getType ()->isIntegerTy ());
			bool two_int (two->value ()->getType ()->isIntegerTy ());
			if (one_int && two_int)
			{
				size_t one_bits (one->value ()->getType ()->getPrimitiveSizeInBits ());
				size_t two_bits (two->value ()->getType ()->getPrimitiveSizeInBits ());
				if (one_bits == two_bits)
				{
					auto instruction (llvm::BinaryOperator::CreateSub (one->value (), two->value ()));
					context_a.results.push_back (boost::make_shared <mu::llvm_::instruction::node> (instruction, one->type));
				}
				else
				{
					std::wstringstream message;
					message << L"Bit widths don't match: ";
					message << one_bits;
					message << L" ";
					message << two_bits;
					(*context_a.errors) (message.str ());
				}
			}
			else
			{
				std::wstringstream message;
				message << L"Arguments are not integers: ";
				message << one_int;
				message << L" ";
				message << two_int;
				(*context_a.errors) (message.str ());
			}
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [1], 1);
		}
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::instructions::sub::count ()
{
	return 2;
}