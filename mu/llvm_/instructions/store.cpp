#include <mu/llvm_/instructions/store.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/void_type/node.h>
#include <mu/script/check.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::llvm_::instructions::store::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::llvm_::value::node, mu::llvm_::value::node> () (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::value::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::value::node *> (context_a.parameters (1)));
		auto ptr (llvm::dyn_cast <llvm::PointerType> (two->value ()->getType ()));
		if (ptr != nullptr)
		{
			if (ptr->getElementType () == one->value ()->getType ())
			{
				auto instruction (new llvm::StoreInst (one->value (), two->value ()));
				context_a.push (new (GC) mu::llvm_::instruction::node (instruction, new (GC) mu::llvm_::void_type::node (new (GC) mu::llvm_::context::node (&instruction->getContext ()))));
			}
			else
			{
				mu::stringstream message;
				message << L"Argument two is not a pointer to the type of argument one";
				context_a.errors (message.str ());
				valid = false;
			}
		}
		else
		{
			mu::stringstream message;
			message << L"Argument 2 is not a pointer";
			context_a.errors (message.str ());
			valid = false;
		}
	}
	return valid;
}