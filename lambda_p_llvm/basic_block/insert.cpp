#include "insert.h"

#include <lambda_p_llvm/basic_block/node.h>
#include <lambda_p_llvm/instruction/node.h>
#include <core/errors/error_target.h>

#include <llvm/BasicBlock.h>

void lambda_p_llvm::basic_block::insert::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::basic_block::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_llvm::instruction::node> (parameters [1]));
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
				(*errors_a) (L"Block is not set");
			}
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

std::wstring lambda_p_llvm::basic_block::insert::name ()
{
	return std::wstring (L"lambda_p_llvm::basic_block::insert");
}