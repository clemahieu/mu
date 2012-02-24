#include "split_return.h"

#include <mu/core/errors/error_target.h>
#include <lambda_p_llvm/value/node.h>
#include <lambda_p_llvm/pointer_type/node.h>
#include <lambda_p_llvm/function_type/node.h>
#include <lambda_p_llvm/set_type/node.h>
#include <lambda_p_llvm/void_type/node.h>
#include <lambda_p_llvm/basic_block/node.h>

#include <boost/make_shared.hpp>

#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>

lambda_p_llvm::basic_block::split_return::split_return (boost::shared_ptr <lambda_p_llvm::basic_block::node> block_a, boost::shared_ptr <lambda_p_script::operation> next_a)
	: next (next_a),
	block (block_a)
{
}

void lambda_p_llvm::basic_block::split_return::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	std::vector <boost::shared_ptr <mu::core::node>> results_l;
	next->perform (errors_a, parameters, results_l);
	if (!(*errors_a) ())
	{
		assert (results_l.size () == 1);
		auto result (boost::static_pointer_cast <lambda_p_llvm::value::node> (results_l [0]));
		auto set (boost::dynamic_pointer_cast <lambda_p_llvm::set_type::node> (result->type));
		if (set.get () != nullptr)
		{
			for (size_t i (0), j (set->elements.size ()); i != j; ++i)
			{
				auto extract (llvm::ExtractValueInst::Create (result->value (), i));
				block->block->getInstList ().push_back (extract);
				auto value (boost::make_shared <lambda_p_llvm::value::node> (extract, set->elements [i]));
				results.push_back (value);
			}
		}
		else
		{
			auto void_l (boost::dynamic_pointer_cast <lambda_p_llvm::void_type::node> (result->type));
			if (void_l.get () != nullptr)
			{
				// Don't return anything for void
			}
			else
			{
				results.push_back (result);
			}
		}
	}
}