#include "split_return.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/value/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/llvm_/function_type/node.h>
#include <mu/llvm_/set_type/node.h>
#include <mu/llvm_/void_type/node.h>
#include <mu/llvm_/basic_block/node.h>

#include <boost/make_shared.hpp>

#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>

mu::llvm_::basic_block::split_return::split_return (boost::shared_ptr <mu::llvm_::basic_block::node> block_a, boost::shared_ptr <mu::script::operation> next_a)
	: next (next_a),
	block (block_a)
{
}

void mu::llvm_::basic_block::split_return::perform (mu::script::context & context_a)
{
	std::vector <boost::shared_ptr <mu::core::node>> results_l;
    auto ctx (mu::script::context (context_a.errors, context_a.parameters, results_l));
	next->perform (ctx);
	if (!(*context_a.errors) ())
	{
		assert (results_l.size () == 1);
		auto result (boost::static_pointer_cast <mu::llvm_::value::node> (results_l [0]));
		auto set (boost::dynamic_pointer_cast <mu::llvm_::set_type::node> (result->type));
		if (set.get () != nullptr)
		{
			for (size_t i (0), j (set->elements.size ()); i != j; ++i)
			{
				auto extract (llvm::ExtractValueInst::Create (result->value (), i));
				block->block->getInstList ().push_back (extract);
				auto value (boost::make_shared <mu::llvm_::value::node> (extract, set->elements [i]));
				context_a.results.push_back (value);
			}
		}
		else
		{
			auto void_l (boost::dynamic_pointer_cast <mu::llvm_::void_type::node> (result->type));
			if (void_l.get () != nullptr)
			{
				// Don't return anything for void
			}
			else
			{
				context_a.results.push_back (result);
			}
		}
	}
}