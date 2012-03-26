#include <mu/llvm_/instructions/zext.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/llvm_/type/node.h>
#include <mu/script/check.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

bool mu::llvm_::instructions::zext::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::llvm_::value::node, mu::llvm_::type::node> () (context_a));
	if (valid)
	{
		auto one (boost::static_pointer_cast <mu::llvm_::value::node> (context_a.parameters (0)));
		auto two (boost::static_pointer_cast <mu::llvm_::type::node> (context_a.parameters (1)));
		bool one_int (one->value ()->getType ()->isIntegerTy ());
		bool two_int (two->type ()->isIntegerTy ());
		if (one_int && two_int)
		{
			size_t one_bits (one->value ()->getType ()->getPrimitiveSizeInBits ());
			size_t two_bits (two->type ()->getPrimitiveSizeInBits ());
			if (one_bits <= two_bits)
			{
				auto instruction (llvm::ZExtInst::CreateZExtOrBitCast (one->value (), two->type ()));
				context_a.push (boost::make_shared <mu::llvm_::instruction::node> (instruction, two));
			}
			else
			{
				std::wstringstream message;
				message << L"Bit width of argument two is not greater than or equal to bit width of argument one: ";
				message << one_bits;
				message << L" ";
				message << two_bits;
				context_a.errors (message.str ());
				valid = false;
			}
		}
		else
		{
			std::wstringstream message;
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