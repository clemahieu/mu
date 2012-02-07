#include "structure.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/instruction/node.h>
#include <lambda_p_llvm/apint/node.h>
#include <lambda_p_llvm/struct_type/node.h>
#include <lambda_p_llvm/context/node.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

void lambda_p_llvm::types::structure::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	if (parameters.size () > 0)
	{
		auto context (boost::dynamic_pointer_cast <lambda_p_llvm::context::node> (parameters [0]));
		if (context.get () != nullptr)
		{
			std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> types;
			bool good (true);
			size_t position (1);
			for (auto i (parameters.begin ()), j (parameters.end ()); i != j && good; ++i, ++position)
			{
				auto one (boost::dynamic_pointer_cast <lambda_p_llvm::type::node> (parameters [position]));
				if (one.get () != nullptr)
				{
					types.push_back (one);
				}
				else
				{
					good = false;
					invalid_type (errors_a, parameters [position], position);
				}
			}
			if (good)
			{
				results.push_back (boost::make_shared <lambda_p_llvm::struct_type::node> (context, types));
			}
		}
		else
		{
			invalid_type (errors_a, parameters [0], 0);
		}
	}
	else
	{
		(*errors_a) (L"Struct type must have at least one argument");
	}
}