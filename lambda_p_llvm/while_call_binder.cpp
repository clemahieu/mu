#include "while_call_binder.h"

#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/so_value.h>
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

void lambda_p_llvm::while_call_binder::bind (::lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_count (0, 2, statement, problems);
	if (problems.empty ())
	{
		::std::vector < size_t>::iterator argument (statement->association->parameters.begin ());		
		::boost::shared_ptr < ::lambda_p_llvm::so_value> condition (::boost::dynamic_pointer_cast < ::lambda_p_llvm::so_value> (instances [*argument]));
		++argument;
		if (condition.get () != NULL)
		{
			::boost::shared_ptr < ::lambda_p_llvm::so_value> function_l (::boost::dynamic_pointer_cast < ::lambda_p_llvm::so_value> (instances [*argument]));
			++argument;
			if (function_l.get () != NULL)
			{
				if (condition->type () == ::llvm::Type::getInt1Ty (context.context))
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
					::llvm::Value * condition_value (condition->operator() ());
					::llvm::BranchInst * done (::llvm::BranchInst::Create (body_block, exit_block, condition_value));
					check_block->getInstList ().push_back (done);
					context.block = body_block;
					::llvm::Value * completion_value (function_l->operator() ());
					::llvm::BranchInst * loop (::llvm::BranchInst::Create (check_block));
					body_block->getInstList ().push_back (loop);
					context.block = exit_block;
				}
				else
				{
					add_error (::std::wstring (L"argument 1 is not a bool"), problems);
				}
			}
			else
			{
				add_error (::std::wstring (L"argument 2 function is not a noop_closure"), problems);
			}
		}
		else
		{
			add_error (::std::wstring (L"argument 1 condition is not a noop_closure"), problems);
		}
	}
}

::std::wstring lambda_p_llvm::while_call_binder::binder_name ()
{
	return ::std::wstring (L"while_call_binder");
}