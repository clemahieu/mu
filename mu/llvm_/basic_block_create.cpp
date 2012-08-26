#include <mu/llvm_/basic_block_create.h>

#include <mu/llvm_/context_node.h>
#include <mu/llvm_/basic_block_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/BasicBlock.h>

#include <gc_cpp.h>

bool mu::llvm_::basic_block::create::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::llvm_::context::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::context::node *> (context_a.parameters (0)));
		context_a.push (new (GC) mu::llvm_::basic_block::node (llvm::BasicBlock::Create (*one->context)));
	}
	return valid;
}