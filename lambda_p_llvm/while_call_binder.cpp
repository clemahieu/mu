#include "while_call_binder.h"

#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/function_binder.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/call_inst_binder.h>
#include <lambda_p_llvm/argument_binder.h>
#include <lambda_p/binder/routine_instances.h>

#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>
#include <llvm/Function.h>

lambda_p_llvm::while_call_binder::while_call_binder (::lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

void lambda_p_llvm::while_call_binder::bind (::lambda_p::core::statement * statement, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	if (statement->association->parameters.size () >= 2)
	{
		if (statement->association->results.size () == 1)
		{
			::std::vector < size_t>::iterator argument (statement->association->parameters.begin ());
			::boost::shared_ptr < ::lambda_p::binder::node_instance> function_instance (instances [*argument]);
			++argument;
			::boost::shared_ptr < ::lambda_p_llvm::function_binder> function_l (::boost::dynamic_pointer_cast < ::lambda_p_llvm::function_binder> (function_instance));
			if (function_l.get () != NULL)
			{
				::boost::shared_ptr < ::lambda_p::binder::node_instance> condition_instance (instances [*argument]);
				++argument;
				::boost::shared_ptr < ::lambda_p_llvm::value> condition (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (condition_instance));
				if (condition.get () != NULL)
				{
					if (condition->value_m->getType () == ::llvm::Type::getInt1PtrTy (context.context))
					{
						::llvm::Function * function (context.block->getParent ());
						::llvm::BasicBlock * check_block (::llvm::BasicBlock::Create (context.context)); // Performs boolean check
						function->getBasicBlockList ().push_back (check_block);
						::llvm::BasicBlock * body_block (::llvm::BasicBlock::Create (context.context)); // Calls target function
						function->getBasicBlockList ().push_back (body_block);
						::llvm::BasicBlock * exit_block (::llvm::BasicBlock::Create (context.context)); // For code following loop
						function->getBasicBlockList ().push_back (exit_block);
						::llvm::BranchInst * entry (::llvm::BranchInst::Create (check_block));
						context.block->getInstList ().push_back (entry);
						::llvm::LoadInst * check_load (new ::llvm::LoadInst (condition->value_m));
						check_block->getInstList ().push_back (check_load);
						::llvm::BranchInst * done (::llvm::BranchInst::Create (body_block, exit_block, check_load));
						check_block->getInstList ().push_back (done);
						context.block = body_block;
						::lambda_p_llvm::call_inst_binder * call (new ::lambda_p_llvm::call_inst_binder (context));
						::std::vector < ::llvm::Value *> arguments;
						::lambda_p_llvm::argument_binder argument_binder;
						::llvm::FunctionType::param_iterator parameter (function_l->function->getFunctionType ()->param_begin ());
						argument_binder.apply (arguments, argument, statement->association->parameters.end (), parameter, function_l->function->getFunctionType ()->param_end (), instances, problems);
						if (problems.empty ())
						{
							::llvm::CallInst * call (::llvm::CallInst::Create (function_l->function, arguments.begin (), arguments.end ()));
							body_block->getInstList ().push_back (call);
							::llvm::BranchInst * loop (::llvm::BranchInst::Create (check_block));
							body_block->getInstList ().push_back (loop);
							context.block = exit_block;
						}
					}
					else
					{
						add_error (::std::wstring (L"argument 2 is not a pointer to a bool"), problems);
					}
				}
				else
				{
					add_error (::std::wstring (L"argument 2 is not a value"), problems);
				}
			}
			else
			{
				add_error (::std::wstring (L"argument 1 is not a function_binder"), problems);
			}
		}
		else
		{
			add_error (::std::wstring (L"expecting 1 result"), problems);
		}
	}
	else
	{
		add_error (::std::wstring (L"expecting at least 2 arguments"), problems);
	}
}

::std::wstring lambda_p_llvm::while_call_binder::binder_name ()
{
	return ::std::wstring (L"while_call_binder");
}