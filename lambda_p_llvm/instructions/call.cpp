#include "call.h"

#include <lambda_p_llvm/value/node.h>
#include <lambda_p_llvm/type/node.h>
#include <lambda_p_script/values/operation.h>
#include <lambda_p_llvm/pointer_type/node.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/function_type/node.h>
#include <lambda_p_llvm/instruction/node.h>
#include <lambda_p_llvm/void_type/node.h>
#include <lambda_p_llvm/type/build.h>
#include <lambda_p_llvm/context/node.h>

#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>

#include <boost/make_shared.hpp>

void lambda_p_llvm::instructions::call::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		auto pointer_type (boost::dynamic_pointer_cast <lambda_p_llvm::pointer_type::node> (one->type));
		if (pointer_type.get () != nullptr)
		{
			auto function_type (boost::dynamic_pointer_cast <lambda_p_llvm::function_type::node> (pointer_type->element));
			if (function_type.get () != nullptr)
			{
				auto flat_type (function_type->function_type ());
				std::vector <llvm::Value *> arguments;
				size_t position (0);
				for (auto i (parameters.begin () + 1), j (parameters.end () + 0); i != j && !(*errors_a) (); ++i, ++position)
				{
					auto value (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (*i));
					if (value.get () != nullptr)
					{
						auto void_type (boost::dynamic_pointer_cast <lambda_p_llvm::void_type::node> (value->type));
						if (void_type.get () == nullptr)
						{
							if (value->type->type () == flat_type->getParamType (position))
							{
								arguments.push_back (value->value ());
							}
							else
							{
								(*errors_a) (L"Expected type doesn't match actual type");
							}
						}
					}
				}
				results.push_back (boost::make_shared <lambda_p_llvm::instruction::node> (llvm::CallInst::Create (one->value (), arguments), function_type->output));
			}
			else
			{
				(*errors_a) (L"Can only call to a pointer to a function type");
			}
		}
		else
		{
			(*errors_a) (L"Can only call to a pointer type");
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}