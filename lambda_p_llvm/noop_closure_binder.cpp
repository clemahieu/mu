#include "noop_closure_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/argument_binder.h>
#include <lambda_p_llvm/noop_closure.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p/binder/list.h>

#include <llvm/Function.h>
#include <llvm/Value.h>

lambda_p_llvm::noop_closure_binder::noop_closure_binder (lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

void lambda_p_llvm::noop_closure_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_llvm::value> function_value (boost::dynamic_pointer_cast <lambda_p_llvm::value> (nodes [statement->association->parameters [0]]));
		if (function_value.get () != NULL)
		{
			llvm::Function * function (llvm::dyn_cast < llvm::Function> (function_value->operator() ()));
			if (function != NULL)
			{
				boost::shared_ptr <lambda_p::binder::list> arguments (boost::dynamic_pointer_cast <lambda_p::binder::list> (nodes [statement->association->parameters [1]]));
				if (arguments.get () != NULL)
				{
					std::vector < llvm::Value *> argument_values;
					::lambda_p_llvm::argument_binder argument_binder;
					argument_binder.apply (argument_values, arguments, function->getFunctionType ()->param_begin (), function->getFunctionType ()->param_end (), nodes, problems);
					if (problems.errors.empty ())
					{
						boost::shared_ptr <lambda_p_llvm::noop_closure> closure (new lambda_p_llvm::noop_closure (context, function, argument_values));
						nodes [statement->association->results [0]] = closure;
					}
				}
				else
				{
					unexpected_binder_type_error (1, std::wstring (L"list"), problems);
				}
			}
			else
			{
				add_error (std::wstring (L"argument 1 must be a function"), problems);
			}
		}
		else
		{
			unexpected_binder_type_error (0, std::wstring (L"llvm_value"), problems);
		}
	}
}

std::wstring lambda_p_llvm::noop_closure_binder::binder_name ()
{
	return std::wstring (L"noop_closure_binder");
}

