#include "call_binder.h"

#include <lambda_p_llvm/noop_closure.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p_llvm/generation_context.h>

#include <llvm/Function.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

void lambda_p_llvm::call_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, lambda_p::errors::error_list & problems)
{
	check_count (0, 1, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_llvm::noop_closure> target (boost::dynamic_pointer_cast <lambda_p_llvm::noop_closure> (instances [statement->association->parameters [0]]));
		if (target.get () != NULL)
		{
			llvm::CallInst * call (llvm::CallInst::Create (target->function, target->arguments.begin (), target->arguments.end ()));
			target->context.block->getInstList ().push_back (call);
		}
		else
		{
			add_error (std::wstring (L"argument 1 must be a noop_closure"), problems);
		}
	}
}

std::wstring lambda_p_llvm::call_binder::binder_name ()
{
	return std::wstring (L"call_binder");
}