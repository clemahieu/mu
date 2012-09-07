#include <mu/llvm_/basic_block_insert.h>

#include <mu/llvm_/basic_block_node.h>
#include <mu/llvm_/instruction_node.h>
#include <mu/core/errors/error_target.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/BasicBlock.h>

bool mu::llvm_::basic_block::insert::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::llvm_::basic_block::node, mu::llvm_::instruction::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::basic_block::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::instruction::node *> (context_a.parameters (1)));
		if (one->block != nullptr)
		{
			one->block->getInstList ().push_back (two->instruction ());
		}
		else
		{
			context_a.errors (U"Block is not set");
			result = false;
		}
	}
	return result;
}