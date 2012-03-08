#include "extract.h"

#include <mu/llvm_/basic_block/node.h>
#include <mu/llvm_/set_type/node.h>
#include <mu/llvm_/value/node.h>
#include <mu/llvm_/instruction/node.h>

#include <boost/make_shared.hpp>

#include <llvm/Instructions.h>

void mu::llvm_::set_type::extract::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::basic_block::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::value::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto set_type (boost::dynamic_pointer_cast <mu::llvm_::set_type::node> (two->type));
			if (set_type.get () != nullptr)
			{
				for (size_t i (0), j (set_type->elements.size ()); i != j; ++i)
				{
					auto extract (llvm::ExtractValueInst::Create (two->value (), i));
					context_a.results.push_back (boost::make_shared <mu::llvm_::instruction::node> (extract, set_type->elements [i]));
				}
			}
			else
			{
				context_a.results.push_back (two);
			}
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [1], 1);
		}
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::set_type::extract::count ()
{
	return 2;
}