#include "call_inst_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/fo_value.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/argument_binder.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p_kernel/list.h>

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>

lambda_p_llvm::call_inst_binder::call_inst_binder (::lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

void lambda_p_llvm::call_inst_binder::bind (::lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.empty ())
	{
		::std::vector < ::llvm::Value *> argument_values;
		::boost::shared_ptr < ::lambda_p_llvm::fo_value> value (::boost::dynamic_pointer_cast < ::lambda_p_llvm::fo_value> (instances [statement->association->parameters [0]]));
		if (value.get () != NULL)
		{
			::llvm::Function * function (::llvm::dyn_cast < ::llvm::Function> (value->value));
			if (function != NULL)
			{
				::boost::shared_ptr < lambda_p_kernel::list> arguments (::boost::dynamic_pointer_cast < lambda_p_kernel::list> (instances [statement->association->parameters [1]]));
				if (arguments.get () != NULL)
				{
					::llvm::FunctionType const * type (function->getFunctionType ());
					::llvm::FunctionType::param_iterator j = type->param_begin ();
					::lambda_p_llvm::argument_binder argument_binder;
					argument_binder.apply (argument_values, arguments, j, type->param_end (), instances, problems);
					if (problems.empty ())
					{
						::llvm::CallInst * call (::llvm::CallInst::Create (value->operator() (), argument_values.begin (), argument_values.end ()));
						context.block->getInstList ().push_back (call);
						::boost::shared_ptr < ::lambda_p_llvm::fo_value> value (new ::lambda_p_llvm::fo_value (call));
						instances [statement->association->results [0]] = value;
					}
				}
				else
				{
					unexpected_binder_type_error (1, ::std::wstring (L"list"), problems);
				}
			}
			else
			{
				add_error (::std::wstring (L"Parameter 1 does not reference a function"), problems);
			}
		}
		else
		{
			unexpected_binder_type_error (0, ::std::wstring (L"fo_value"), problems);
		}
	}
}

::std::wstring lambda_p_llvm::call_inst_binder::binder_name ()
{
	return ::std::wstring (L"call_inst_binder");
}

void lambda_p_llvm::call_inst_binder::validate_argument_types (::lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
}