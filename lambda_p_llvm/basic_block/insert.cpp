#include "insert.h"

#include <lambda_p_llvm/basic_block/node.h>
#include <lambda_p_llvm/instruction/node.h>

#include <llvm/BasicBlock.h>

void lambda_p_llvm::basic_block::insert::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::basic_block::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_llvm::instruction::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			one->block->getInstList ().push_back (two->instruction ());
		}
		else
		{
			invalid_type (errors_a, parameters [1], 1);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_llvm::basic_block::insert::count ()
{
	return 2;
}