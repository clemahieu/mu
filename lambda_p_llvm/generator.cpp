#include "generator.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p_llvm/type.h>
#include <lambda_p_llvm/fo_value.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_llvm/so_value.h>
#include <lambda_p_llvm/function_binder.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p_kernel/list.h>

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Module.h>
#include <llvm/Instructions.h>

#include <sstream>

lambda_p_llvm::generator::generator (::lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

void lambda_p_llvm::generator::bind (::lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	size_t position;
	check_count (1, 3, statement, problems);
	if (problems.empty ())
	{
		::boost::shared_ptr < lambda_p_kernel::routine> routine (::boost::dynamic_pointer_cast < lambda_p_kernel::routine> (instances [statement->association->parameters [0]]));
		if (routine.get () != NULL)
		{
			::boost::shared_ptr < ::lambda_p_llvm::type> return_type (::boost::dynamic_pointer_cast < ::lambda_p_llvm::type> (instances [statement->association->parameters [1]]));
			if (return_type.get () != NULL)
			{
				::boost::shared_ptr < lambda_p_kernel::list> argument_list (::boost::dynamic_pointer_cast < lambda_p_kernel::list> (instances [statement->association->parameters [2]]));
				if (argument_list.get () != NULL)
				{
					if (argument_list->instances.size () == routine->routine_m->surface->results.size ())
					{
						::std::vector < size_t> open_positions;
						::std::vector < ::llvm::Type const *> parameters;
						position = 0;
						::llvm::BasicBlock * block (::llvm::BasicBlock::Create (context.context));
						::lambda_p_llvm::generation_context context_l (context.context, context.module, block);
						for (::std::vector < ::boost::shared_ptr < ::lambda_p::binder::instance> >::iterator i = argument_list->instances.begin (); i != argument_list->instances.end (); ++i, ++position)
						{
							::boost::shared_ptr < ::lambda_p::binder::instance> instance (*i);
							::boost::shared_ptr < ::lambda_p_llvm::type> type (::boost::dynamic_pointer_cast < ::lambda_p_llvm::type> (instance));
							if (type.get () != NULL)
							{
								parameters.push_back (type->type_m);
								open_positions.push_back (position);
							}
							else
							{
								::boost::shared_ptr < ::lambda_p_llvm::fo_value> value (::boost::dynamic_pointer_cast < ::lambda_p_llvm::fo_value> (instance));
								if (value.get () != NULL)
								{
									::llvm::Function * function (::llvm::dyn_cast < ::llvm::Function> (value->value));
									if (function != NULL)
									{
										routine->routine_m->instances [position] = ::boost::shared_ptr < ::lambda_p_llvm::function_binder> (new ::lambda_p_llvm::function_binder (context_l, function));
									}
									else
									{
										routine->routine_m->instances [position] = value;
									}
								}
								else
								{
									unexpected_binder_type_error (position, ::std::wstring (L"type or fo_value"), problems);
								}
							}
						}
						if (problems.empty ())
						{
							::llvm::Function * function (::llvm::Function::Create (::llvm::FunctionType::get (return_type->type_m, parameters, false), ::llvm::GlobalValue::ExternalLinkage));
							function->getBasicBlockList ().push_back (block);
							::llvm::Function::arg_iterator i (function->arg_begin ());
							::std::vector < size_t >::iterator j (open_positions.begin ());
							for (; i != function->arg_end (); ++i, ++j)
							{
								routine->routine_m->instances [*j] = ::boost::shared_ptr < ::lambda_p_llvm::fo_value> (new ::lambda_p_llvm::fo_value (&(*i)));
							}
							lambda_p_kernel::bind_procedure procedure (routine->routine_m);
							procedure (problems);
							if (problems.empty ())
							{
								::boost::shared_ptr < ::lambda_p_llvm::fo_value> return_value (::boost::dynamic_pointer_cast < ::lambda_p_llvm::fo_value> (routine->routine_m->instances [routine->routine_m->surface->parameters [0]]));
								if (return_value.get () != NULL)
								{
									::llvm::ReturnInst * ret (::llvm::ReturnInst::Create (context_l.context, return_value->value));
									context_l.block->getInstList ().push_back (ret);
									context.module->getFunctionList ().push_back (function);
									::boost::shared_ptr < ::lambda_p_llvm::fo_value> value (new ::lambda_p_llvm::fo_value (function));
									instances [statement->association->results [0]] = value;
								}
								else
								{
									add_error (::std::wstring (L"result value is not an llvm value"), problems);
								}
							}
						}
					}
					else
					{
						::std::wstringstream message;
						message << L"Unexpected number of arguments, have: ";
						message << argument_list->instances.size ();
						message << L" expect: ";
						message << routine->routine_m->surface->parameters.size ();
						add_error (message.str (), problems);
					}
				}
				else
				{
					unexpected_binder_type_error (2, ::std::wstring (L"group"), problems);
				}
			}
			else
			{
				unexpected_binder_type_error (1, ::std::wstring (L"type"), problems);
			}
		}
		else
		{
			unexpected_binder_type_error (0, ::std::wstring (L"routine"), problems);
		}
	}
}

::std::wstring lambda_p_llvm::generator::binder_name ()
{
	return ::std::wstring (L"generator");
}
