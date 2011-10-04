#include "call_inst_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/function_binder.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/generation_context.h>

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>

lambda_p_llvm::call_inst_binder::call_inst_binder (::lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

void lambda_p_llvm::call_inst_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_only_references (statement, problems);
	::std::vector < ::llvm::Value *> arguments;
	::std::vector < ::lambda_p::core::node *>::iterator i = statement->association->parameters.begin ();
	if (i != statement->association->parameters.end ())
	{
		::boost::shared_ptr < ::lambda_p::binder::node_instance> function_instance (instances [*i]);
		::boost::shared_ptr < ::lambda_p_llvm::function_binder> function (::boost::dynamic_pointer_cast < ::lambda_p_llvm::function_binder> (function_instance));
		++i;
		if (function.get () != NULL)
		{
			::llvm::FunctionType const * type (function->function->getFunctionType ());
			::llvm::FunctionType::param_iterator j = type->param_begin ();
			while (i != statement->association->parameters.end () && j != type->param_end ())
			{
				::boost::shared_ptr < ::lambda_p::binder::node_instance> value_instance (instances [*i]);
				::boost::shared_ptr < ::lambda_p_llvm::value> value (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (value_instance));
				if (value.get () != NULL)
				{
					if (value->value_m->getType () == *j)
					{
						arguments.push_back (value->value_m);
					}
					else
					{
						add_error (::std::wstring (L"Argument type does not match parameter type"), problems);
					}
				}
				else
				{
					add_error (::std::wstring (L"Argument is not a value"), problems);
				}
				++i;
				++j;
			}
			if ((i == statement->association->parameters.end ()) != (j == type->param_end ()))
			{
				add_error (::std::wstring (L"Incorrect number of arguments"), problems);
			}
			if (problems.empty ())
			{
				::llvm::CallInst * call (::llvm::CallInst::Create (function->function, arguments.begin (), arguments.end ()));
				::boost::shared_ptr < ::lambda_p_llvm::value> value (new ::lambda_p_llvm::value (call));
				context.block->getInstList ().push_back (call);
			}
		}
		else
		{
			add_error (::std::wstring (L"Parameter 1 is not a function_binder"), problems);
		}
	}
	else
	{
		add_error (::std::wstring (L"Function required"), problems);
	}
}

::std::wstring lambda_p_llvm::call_inst_binder::binder_name ()
{
	return ::std::wstring (L"call_inst_binder");
}

void lambda_p_llvm::call_inst_binder::validate_argument_types (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
}