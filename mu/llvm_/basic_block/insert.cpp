#include "insert.h"

#include <mu/llvm_/basic_block/node.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/core/errors/error_target.h>
#include <mu/script/check.h>

#include <llvm/BasicBlock.h>

void mu::llvm_::basic_block::insert::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::basic_block::node, mu::llvm_::instruction::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::basic_block::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::llvm_::instruction::node> (context_a.parameters [1]));
		if (one->block != nullptr)
		{
			one->block->getInstList ().push_back (two->instruction ());
		}
		else
		{
			context_a (L"Block is not set");
		}
	}
}

std::wstring mu::llvm_::basic_block::insert::name ()
{
	return std::wstring (L"mu::llvm_::basic_block::insert");
}