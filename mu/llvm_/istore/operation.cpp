#include "operation.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/value/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/llvm_/instructions/store.h>
#include <mu/script/check.h>

#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <boost/make_shared.hpp>

mu::llvm_::istore::operation::operation (boost::shared_ptr <mu::llvm_::basic_block::node> block_a)
	: block (block_a)
{
}

void mu::llvm_::istore::operation::operator () (mu::script::context & context_a)
{	
	if (mu::script::check <mu::llvm_::value::node, mu::llvm_::value::node, mu::llvm_::value::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::value::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::llvm_::value::node> (context_a.parameters [1]));
		auto three (boost::static_pointer_cast <mu::llvm_::value::node> (context_a.parameters [2]));
		auto ptr (boost::dynamic_pointer_cast <mu::llvm_::pointer_type::node> (two->type));
		if (ptr != nullptr)
		{
			auto offset (boost::dynamic_pointer_cast <mu::llvm_::integer_type::node>  (three->type));
			if (offset.get () != nullptr)
			{			
				auto as_int (new llvm::PtrToIntInst (three->value (), offset->integer_type ()));
				block->block->getInstList ().push_back (as_int);
				auto added (llvm::BinaryOperator::CreateAdd (as_int, three->value ()));
				block->block->getInstList ().push_back (added);
				auto final (boost::make_shared <mu::llvm_::value::node> (added, three->type));
				mu::llvm_::instructions::store store;
				std::vector <boost::shared_ptr <mu::core::node>> a1;
				a1.push_back (one);
				a1.push_back (final);
                auto ctx (mu::script::context (context_a.errors, a1, context_a.results));
				store (ctx);
			}
			else
			{
				(*context_a.errors) (L"Argument 3 is not an integer");
			}
		}
		else
		{
			(*context_a.errors) (L"Argument 2 is not a pointer");
		}
	}
}