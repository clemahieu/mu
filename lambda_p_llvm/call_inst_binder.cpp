#include "call_inst_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/literal_value.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/argument_binder.h>
#include <lambda_p/binder/routine_instances.h>

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>

lambda_p_llvm::call_inst_binder::call_inst_binder (::lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

void lambda_p_llvm::call_inst_binder::bind (::lambda_p::core::statement * statement, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	::std::vector < ::llvm::Value *> arguments;
	::std::vector < size_t>::iterator i = statement->association->parameters.begin ();
	if (statement->association->results.size () == 1)
	{
		if (i != statement->association->parameters.end ())
		{
			::boost::shared_ptr < ::lambda_p::binder::node_instance> function_instance (instances [*i]);
			::boost::shared_ptr < ::lambda_p_llvm::literal_value> value (::boost::dynamic_pointer_cast < ::lambda_p_llvm::literal_value> (function_instance));
			++i;
			if (value.get () != NULL)
			{
				::llvm::Function * function (::llvm::dyn_cast < ::llvm::Function> (value->value));
				if (function != NULL)
				{
					::llvm::FunctionType const * type (function->getFunctionType ());
					::llvm::FunctionType::param_iterator j = type->param_begin ();
					::lambda_p_llvm::argument_binder argument_binder;
					argument_binder.apply (arguments, i, statement->association->parameters.end (), j, type->param_end (), instances, problems);
					if (problems.empty ())
					{
						::llvm::CallInst * call (::llvm::CallInst::Create (value->operator() (), arguments.begin (), arguments.end ()));
						context.block->getInstList ().push_back (call);
						::boost::shared_ptr < ::lambda_p_llvm::literal_value> value (new ::lambda_p_llvm::literal_value (call));
						instances [statement->association->results [0]] = value;
					}
				}
				else
				{
					add_error (::std::wstring (L"Parameter 1 does not reference a function"), problems);
				}
			}
			else
			{
				add_error (::std::wstring (L"Parameter 1 is not a literal_value"), problems);
			}
		}
		else
		{
			add_error (::std::wstring (L"Function required"), problems);
		}
	}
	else
	{
		add_error (::std::wstring (L"Requires exactly 1 result"), problems);
	}
}

::std::wstring lambda_p_llvm::call_inst_binder::binder_name ()
{
	return ::std::wstring (L"call_inst_binder");
}

void lambda_p_llvm::call_inst_binder::validate_argument_types (::lambda_p::core::statement * statement, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
}