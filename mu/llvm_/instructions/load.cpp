#include <mu/llvm_/instructions/load.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/script/check.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::llvm_::instructions::load::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::llvm_::value::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::value::node *> (context_a.parameters (0)));
		auto one_ptr (dynamic_cast <mu::llvm_::pointer_type::node *> (one->type));
		if (one_ptr != nullptr)
		{
			auto instruction (new llvm::LoadInst (one->value ()));
			context_a.push (new (GC) mu::llvm_::instruction::node (instruction, one_ptr->element));
		}
		else
		{
			mu::stringstream message;
			message << L"Argument is not a pointer";
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;
}