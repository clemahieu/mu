#include <mu/llvm_/basic_block/store.h>

#include <mu/llvm_/basic_block/node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

bool mu::llvm_::basic_block::store::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::llvm_::basic_block::node, mu::llvm_::basic_block::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::basic_block::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::basic_block::node *> (context_a.parameters (1)));
		one->block = two->block;
	}
	return valid;
}