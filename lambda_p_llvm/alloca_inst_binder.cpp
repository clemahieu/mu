#include "alloca_inst_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/type.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p/binder/list.h>
#include <lambda_p/errors/error_list.h>

#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>

void lambda_p_llvm::alloca_inst_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.errors.empty ())
	{
		auto block (boost::dynamic_pointer_cast <lambda_p_llvm::value> (nodes [statement->association->references [0]]));
		check_binder (block, 0, L"value", problems);
		auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type> (nodes [statement->association->references [0]]));
		check_binder (type, 1, L"type", problems);
		if (problems.errors.empty ())
		{
			auto block_p (llvm::dyn_cast <llvm::BasicBlock> (block->value_m));
			if (block_p != nullptr)
			{
				llvm::AllocaInst * alloc (new llvm::AllocaInst (type->type_m));
				block_p->getInstList ().push_back (alloc);
				nodes [statement->association->declarations [0]] = boost::shared_ptr <lambda_p_llvm::value> (new lambda_p_llvm::value (alloc));
			}
			else
			{
				add_error (L"Value is not a basic block", problems);
			}
		}
	}
}

std::wstring lambda_p_llvm::alloca_inst_binder::binder_name ()
{
	return std::wstring (L"alloca_inst_binder");
}