#include <mu/llvm_/basic_block/insert.h>

#include <mu/llvm_/basic_block/node.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/core/errors/error_target.h>
#include <mu/script/check.h>

#include <llvm/BasicBlock.h>

bool mu::llvm_::basic_block::insert::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::llvm_::basic_block::node, mu::llvm_::instruction::node> () (context_a));
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
			context_a.errors (L"Block is not set");
			result = false;
		}
	}
	return result;
}

std::wstring mu::llvm_::basic_block::insert::name ()
{
	return std::wstring (L"mu::llvm_::basic_block::insert");
}