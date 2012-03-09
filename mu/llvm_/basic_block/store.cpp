#include "store.h"

#include <mu/llvm_/basic_block/node.h>
#include <mu/script/check.h>

void mu::llvm_::basic_block::store::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::basic_block::node, mu::llvm_::basic_block::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::basic_block::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::llvm_::basic_block::node> (context_a.parameters [1]));
		one->block = two->block;
	}
}