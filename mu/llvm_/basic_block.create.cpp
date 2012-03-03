#include <mu/llvm_/basic_block.create.h>

#include <mu/llvm_/context.node.h>
#include <mu/llvm_/basic_block.node.h>

#include <llvm/BasicBlock.h>

#include <boost/make_shared.hpp>

void mu::llvm_::basic_block::create::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::context::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		results.push_back (boost::make_shared <mu::llvm_::basic_block::node> (llvm::BasicBlock::Create (*one->context)));
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::llvm_::basic_block::create::count ()
{
	return 1;
}
