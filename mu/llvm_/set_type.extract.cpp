#include <mu/llvm_/set_type.extract.h>

#include <mu/llvm_/basic_block.node.h>
#include <mu/llvm_/set_type.node.h>
#include <mu/llvm_/value.node.h>
#include <mu/llvm_/instruction.node.h>

#include <boost/make_shared.hpp>

#include <llvm/Instructions.h>

void mu::llvm_::set_type::extract::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::basic_block::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::value::node> (parameters [1]));
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
					results.push_back (boost::make_shared <mu::llvm_::instruction::node> (extract, set_type->elements [i]));
				}
			}
			else
			{
				results.push_back (two);
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

size_t mu::llvm_::set_type::extract::count ()
{
	return 2;
}
