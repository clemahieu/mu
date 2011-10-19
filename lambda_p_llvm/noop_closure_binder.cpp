#include "noop_closure_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/argument_binder.h>
#include <lambda_p_llvm/noop_closure.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p_kernel/list.h>

#include <llvm/Function.h>
#include <llvm/Value.h>

lambda_p_llvm::noop_closure_binder::noop_closure_binder (lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

void lambda_p_llvm::noop_closure_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, std::vector < boost::shared_ptr < lambda_p::errors::error> > & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.empty ())
	{
		boost::shared_ptr < lambda_p_llvm::value> function_value (boost::dynamic_pointer_cast < lambda_p_llvm::value> (instances [statement->association->parameters [0]]));
		if (function_value.get () != NULL)
		{
			llvm::Function * function (llvm::dyn_cast < llvm::Function> (function_value->operator() ()));
			if (function != NULL)
			{
				boost::shared_ptr < lambda_p_kernel::list> arguments (boost::dynamic_pointer_cast < lambda_p_kernel::list> (instances [statement->association->parameters [1]]));
				if (arguments.get () != NULL)
				{
					std::vector < llvm::Value *> argument_values;
					::lambda_p_llvm::argument_binder argument_binder;
					argument_binder.apply (argument_values, arguments, function->getFunctionType ()->param_begin (), function->getFunctionType ()->param_end (), instances, problems);
					if (problems.empty ())
					{
						boost::shared_ptr < lambda_p_llvm::noop_closure> closure (new lambda_p_llvm::noop_closure (context, function, argument_values));
						instances [statement->association->results [0]] = closure;
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

