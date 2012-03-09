#include "create.h"

#include <mu/llvm_/context/node.h>
#include <mu/llvm_/basic_block/node.h>
#include <mu/script/check.h>

#include <llvm/BasicBlock.h>

#include <boost/make_shared.hpp>

void mu::llvm_::basic_block::create::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::context::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::context::node> (context_a.parameters [0]));
		context_a.results.push_back (boost::make_shared <mu::llvm_::basic_block::node> (llvm::BasicBlock::Create (*one->context)));
	}
}

size_t mu::llvm_::basic_block::create::count ()
{
	return 1;
}