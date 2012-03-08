#include "zext.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/llvm_/type/node.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::instructions::zext::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::value::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::type::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			bool one_int (one->value ()->getType ()->isIntegerTy ());
			bool two_int (two->type ()->isIntegerTy ());
			if (one_int && two_int)
			{
				size_t one_bits (one->value ()->getType ()->getPrimitiveSizeInBits ());
				size_t two_bits (two->type ()->getPrimitiveSizeInBits ());
				if (one_bits <= two_bits)
				{
					auto instruction (llvm::ZExtInst::CreateZExtOrBitCast (one->value (), two->type ()));
					context_a.results.push_back (boost::make_shared <mu::llvm_::instruction::node> (instruction, two));
				}
				else
				{
					std::wstringstream message;
					message << L"Bit width of argument two is not greater than or equal to bit width of argument one: ";
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

size_t mu::llvm_::instructions::zext::count ()
{
	return 2;
}