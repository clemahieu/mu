#include <mu/llvm_/istore/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/value/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/llvm_/instructions/store.h>
#include <mu/script/check.h>

#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <boost/make_shared.hpp>

#include <gc_cpp.h>

mu::llvm_::istore::operation::operation (boost::shared_ptr <mu::llvm_::basic_block::node> block_a)
	: block (block_a)
{
}

bool mu::llvm_::istore::operation::operator () (mu::script::context & context_a)
{	
	bool valid (mu::script::check <mu::llvm_::value::node, mu::llvm_::value::node, mu::llvm_::value::node> () (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::value::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::value::node *> (context_a.parameters (1)));
		auto three (static_cast <mu::llvm_::value::node *> (context_a.parameters (2)));
		auto ptr (dynamic_cast <mu::llvm_::pointer_type::node *> (two->type));
		if (ptr != nullptr)
		{
			auto offset (dynamic_cast <mu::llvm_::integer_type::node *>  (three->type));
			if (offset != nullptr)
			{			
				auto as_int (new llvm::PtrToIntInst (three->value (), offset->integer_type ()));
				block->block->getInstList ().push_back (as_int);
				auto added (llvm::BinaryOperator::CreateAdd (as_int, three->value ()));
				block->block->getInstList ().push_back (added);
				auto final (new (GC) mu::llvm_::value::node (added, three->type));
				context_a.push (new (GC) mu::llvm_::instructions::store);
				context_a.push (one);
				context_a.push (final);
				valid = context_a ();
			}
			else
			{
				context_a.errors (L"Argument 3 is not an integer");
				valid = false;
			}
		}
		else
		{
			context_a.errors (L"Argument 2 is not a pointer");
			valid = false;
		}
	}
	return valid;
}