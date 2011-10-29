#include "call_inst_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/fo_value.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/argument_binder.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p/binder/list.h>

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>

lambda_p_llvm::call_inst_binder::call_inst_binder (lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

void lambda_p_llvm::call_inst_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.errors.empty ())
	{
		std::vector <llvm::Value *> argument_values;
		boost::shared_ptr <lambda_p_llvm::fo_value> value (boost::dynamic_pointer_cast <lambda_p_llvm::fo_value> (nodes [statement->association->references [0]]));
		if (value.get () != nullptr)
		{
			llvm::Function * function (llvm::dyn_cast <llvm::Function> (value->value));
			if (function != nullptr)
			{
				boost::shared_ptr <lambda_p::binder::list> arguments (boost::dynamic_pointer_cast <lambda_p::binder::list> (nodes [statement->association->references [1]]));
				if (arguments.get () != nullptr)
				{
					llvm::FunctionType const * type (function->getFunctionType ());
					llvm::FunctionType::param_iterator j = type->param_begin ();
					::lambda_p_llvm::argument_binder argument_binder;
					argument_binder.apply (argument_values, arguments, j, type->param_end (), nodes, problems);
					if (problems.errors.empty ())
					{
						llvm::CallInst * call (llvm::CallInst::Create (value->operator() (), argument_values.begin (), argument_values.end ()));
						context.block->getInstList ().push_back (call);
						boost::shared_ptr <lambda_p_llvm::fo_value> value (new lambda_p_llvm::fo_value (call));
						nodes [statement->association->declarations [0]] = value;
					}
				}
				else
				{
					unexpected_binder_type_error (1, std::wstring (L"list"), problems);
				}
			}
			else
			{
				add_error (std::wstring (L"Parameter 1 does not reference a function"), problems);
			}
		}
		else
		{
			unexpected_binder_type_error (0, std::wstring (L"fo_value"), problems);
		}
	}
}

std::wstring lambda_p_llvm::call_inst_binder::binder_name ()
{
	return std::wstring (L"call_inst_binder");
}

void lambda_p_llvm::call_inst_binder::validate_argument_types (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
}