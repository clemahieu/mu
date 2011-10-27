#include "alloca_inst_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/type.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/fo_value.h>
#include <lambda_p/binder/routine_instances.h>

#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>

lambda_p_llvm::alloca_inst_binder::alloca_inst_binder (lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

void lambda_p_llvm::alloca_inst_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p::binder::instance> type_instance (instances [statement->association->parameters [0]]);
		boost::shared_ptr <lambda_p_llvm::type> type (boost::dynamic_pointer_cast <lambda_p_llvm::type> (type_instance));
		if (type.get () != NULL)
		{
			llvm::AllocaInst * alloc (new llvm::AllocaInst (type->type_m));
			context.block->getInstList ().push_back (alloc);
			boost::shared_ptr <lambda_p_llvm::fo_value> value (new lambda_p_llvm::fo_value (alloc));
			instances [statement->association->results [0]] = value;
		}
		else
		{
			add_error (std::wstring (L"Expecting argument 1 to be a type"), problems);
		}
	}
}

std::wstring lambda_p_llvm::alloca_inst_binder::binder_name ()
{
	return std::wstring (L"alloca_inst_binder");
}