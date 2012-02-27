#include "operation.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/value/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/llvm_/instructions/store.h>

#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <boost/make_shared.hpp>

mu::llvm_::istore::operation::operation (boost::shared_ptr <mu::llvm_::basic_block::node> block_a)
	: block (block_a)
{
}

void mu::llvm_::istore::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{	
	auto one (boost::dynamic_pointer_cast <mu::llvm_::value::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::value::node> (parameters [1]));
	auto three (boost::dynamic_pointer_cast <mu::llvm_::value::node> (parameters [2]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			if (three.get () != nullptr)
			{
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
						store.perform (errors_a, a1, results);
					}
					else
					{
						(*errors_a) (L"Argument 3 is not an integer");
					}
				}
				else
				{
					(*errors_a) (L"Argument 2 is not a pointer");
				}
			}
			else
			{
				invalid_type (errors_a, parameters [2], 2);
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

size_t mu::llvm_::istore::operation::count ()
{
	return 3;
}