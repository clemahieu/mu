#include "insert.h"

#include <mu/llvm_/basic_block/node.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/core/errors/error_target.h>

#include <llvm/BasicBlock.h>

void mu::llvm_::basic_block::insert::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::basic_block::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::instruction::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			if (one->block != nullptr)
			{
				one->block->getInstList ().push_back (two->instruction ());
			}
			else
			{
				(*context_a.errors) (L"Block is not set");
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

size_t mu::llvm_::basic_block::insert::count ()
{
	return 2;
}

std::wstring mu::llvm_::basic_block::insert::name ()
{
	return std::wstring (L"mu::llvm_::basic_block::insert");
}