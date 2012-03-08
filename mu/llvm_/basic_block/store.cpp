#include "store.h"

#include <mu/llvm_/basic_block/node.h>

void mu::llvm_::basic_block::store::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::basic_block::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::basic_block::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			one->block = two->block;
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

size_t mu::llvm_::basic_block::store::count ()
{
	return 2;
}