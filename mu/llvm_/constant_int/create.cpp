#include <mu/llvm_/constant_int/create.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/apint/node.h>
#include <mu/llvm_/constant_int/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/script/check.h>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::llvm_::constant_int::create::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::llvm_::context::node, mu::llvm_::apint::node, mu::llvm_::apint::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::context::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::apint::node *> (context_a.parameters (1)));
		auto three (static_cast <mu::llvm_::apint::node *> (context_a.parameters (2)));
		auto bits (two->value->getLimitedValue ());
		if (bits >= llvm::IntegerType::MIN_INT_BITS && bits <= llvm::IntegerType::MAX_INT_BITS)
		{
			if (three->value->getActiveBits () <= bits)
			{
				auto type (llvm::Type::getIntNTy (*one->context, bits));
				context_a.push (new (GC) mu::llvm_::constant_int::node (llvm::ConstantInt::get (*one->context, llvm::APInt (bits, three->value->getLimitedValue ())), new (GC) mu::llvm_::integer_type::node (type)));
			}
			else
			{
				mu::stringstream message;
				message << L"Number: ";
				message << three->value->getLimitedValue ();
				message << L" does not fit in: ";
				message << bits;
				message << L" bits";
				context_a.errors (message.str ());
				valid = false;
			}
		}
		else
		{
			mu::stringstream message;
			message << L"Number of bits: ";
			message << bits;
			message << L" is not between: ";
			message << llvm::IntegerType::MIN_INT_BITS;
			message << L" and: ";
			message << llvm::IntegerType::MAX_INT_BITS;
			context_a.errors (message.str ());
			valid = false;
		}
	}
	return valid;
}