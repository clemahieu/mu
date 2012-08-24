#include <mu/llvm_/instructions/add.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/llvm_/ctx.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::llvm_::instructions::add::operator () (mu::llvm_::ctx & context_a)
{
    bool valid (context_a.check <mu::llvm_::value::node, mu::llvm_::value::node> ());
    if (valid)
    {        
		auto one (static_cast <mu::llvm_::value::node *> (context_a.working [0]));
		auto two (static_cast <mu::llvm_::value::node *> (context_a.working [1]));
        auto result (core (context_a.errors, one, two));
        valid = result != nullptr;
        context_a.working.push_back (result);
    }
    return valid;
}

bool mu::llvm_::instructions::add::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::llvm_::value::node, mu::llvm_::value::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::value::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::value::node *> (context_a.parameters (1)));
        auto result (core(context_a.errors, one, two));
        valid = result != nullptr;
        context_a.push (result);
	}
	return valid;
}

auto mu::llvm_::instructions::add::core (mu::core::errors::error_target & errors_a, mu::llvm_::value::node * one, mu::llvm_::value::node * two) -> mu::llvm_::value::node *
{
    mu::llvm_::value::node * result (nullptr);
    bool one_int (one->value ()->getType ()->isIntegerTy ());
    bool two_int (two->value ()->getType ()->isIntegerTy ());
    if (one_int && two_int)
    {
        size_t one_bits (one->value ()->getType ()->getPrimitiveSizeInBits ());
        size_t two_bits (two->value ()->getType ()->getPrimitiveSizeInBits ());
        if (one_bits == two_bits)
        {
            auto instruction (llvm::BinaryOperator::CreateAdd (one->value (), two->value ()));
            result = new (GC) mu::llvm_::instruction::node (instruction, one->type);
        }
        else
        {
            mu::stringstream message;
            message << L"Bit widths don't match: ";
            message << one_bits;
            message << L" ";
            message << two_bits;
            errors_a (message.str ());
        }
    }
    else
    {
        mu::stringstream message;
        message << L"Arguments are not integers: ";
        message << one_int;
        message << L" ";
        message << two_int;
        errors_a (message.str ());
    }
    return result;
}