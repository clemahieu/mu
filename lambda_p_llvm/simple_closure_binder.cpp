#include "simple_closure_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/argument_binder.h>
#include <lambda_p_llvm/simple_closure.h>
#include <lambda_p/binder/routine_instances.h>

#include <llvm/Function.h>
#include <llvm/Value.h>

lambda_p_llvm::simple_closure_binder::simple_closure_binder (::lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

void lambda_p_llvm::simple_closure_binder::bind (::lambda_p::core::statement * statement, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	if (statement->association->results.size () == 1)
	{
		if (statement->association->parameters.size () > 0)
		{
			::std::vector < size_t>::iterator i = statement->association->parameters.begin ();
			::boost::shared_ptr < ::lambda_p_llvm::value> function_value (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (instances [*i]));
			if (function_value.get () != NULL)
			{
				++i;
				::llvm::Function * function (::llvm::dyn_cast < ::llvm::Function> (function_value->operator() ()));
				if (function != NULL)
				{
					::std::vector < ::llvm::Value *> arguments;
					::lambda_p_llvm::argument_binder argument_binder;
					argument_binder.apply (arguments, i, statement->association->parameters.end (), function->getFunctionType ()->param_begin (), function->getFunctionType ()->param_end (), instances, problems);
					if (problems.empty ())
					{
						::boost::shared_ptr < ::lambda_p_llvm::simple_closure> closure (new ::lambda_p_llvm::simple_closure (context, function, arguments));
						instances [statement->association->results [0]] = closure;
					}
				}
				else
				{
					add_error (::std::wstring (L"argument 1 must be a function"), problems);
				}
			}
			else
			{
				add_error (::std::wstring (L"argument 1 must be an llvm value"), problems);
			}
		}
		else
		{
			add_error (::std::wstring (L"expecting at least 1 argument"), problems);
		}
	}
	else
	{
		add_error (::std::wstring (L"expecting 1 result"), problems);
	}
}

::std::wstring lambda_p_llvm::simple_closure_binder::binder_name ()
{
	return ::std::wstring (L"simple_closure_binder");
}

