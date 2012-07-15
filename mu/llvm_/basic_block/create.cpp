#include <mu/llvm_/basic_block/create.h>

#include <mu/llvm_/context/node.h>
#include <mu/llvm_/basic_block/node.h>
#include <mu/script/check.h>

#include <llvm/BasicBlock.h>

#include <gc_cpp.h>

bool mu::llvm_::basic_block::create::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::llvm_::context::node> () (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::context::node *> (context_a.parameters (0)));
		context_a.push (new (GC) mu::llvm_::basic_block::node (llvm::BasicBlock::Create (*one->context)));
	}
	return valid;
}