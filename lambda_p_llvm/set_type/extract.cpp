#include "extract.h"

#include <lambda_p_llvm/basic_block/node.h>
#include <lambda_p_llvm/set_type/node.h>
#include <lambda_p_llvm/value/node.h>
#include <lambda_p_llvm/instruction/node.h>

#include <boost/make_shared.hpp>

#include <llvm/Instructions.h>

void lambda_p_llvm::set_type::extract::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::basic_block::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto set_type (boost::dynamic_pointer_cast <lambda_p_llvm::set_type::node> (two->type));
			if (set_type.get () != nullptr)
			{
				for (size_t i (0), j (set_type->elements.size ()); i != j; ++i)
				{
					auto extract (llvm::ExtractValueInst::Create (two->value (), i));
					results.push_back (boost::make_shared <lambda_p_llvm::instruction::node> (extract, set_type->elements [i]));
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

size_t lambda_p_llvm::set_type::extract::count ()
{
	return 2;
}