#include <mu/llvm_/set_type/extract.h>

#include <mu/llvm_/basic_block/node.h>
#include <mu/llvm_/set_type/node.h>
#include <mu/llvm_/value/node.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/script/check.h>

#include <llvm/Instructions.h>

#include <gc_cpp.h>

bool mu::llvm_::set_type::extract::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::llvm_::basic_block::node, mu::llvm_::value::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::basic_block::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::value::node *> (context_a.parameters (1)));
		auto set_type (dynamic_cast <mu::llvm_::set_type::node *> (two->type));
		if (set_type != nullptr)
		{
			for (size_t i (0), j (set_type->elements.size ()); i != j; ++i)
			{
				auto extract (llvm::ExtractValueInst::Create (two->value (), i));
				context_a.push (new (GC) mu::llvm_::instruction::node (extract, set_type->elements [i]));
			}
		}
		else
		{
			context_a.push (two);
		}
	}
	return result;
}