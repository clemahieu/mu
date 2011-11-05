#include "module_binder.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/context.h>
#include <lambda_p_kernel/adata.h>
#include <lambda_p/binder/list.h>
#include <lambda_p_llvm/module.h>

#include <llvm/Module.h>

void lambda_p_llvm::module_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_kernel::adata> adata (boost::dynamic_pointer_cast <lambda_p_kernel::adata> (nodes [statement->association->references [0]]));
		check_binder (adata, 0, L"adata", problems);
		boost::shared_ptr <lambda_p_llvm::context> context (boost::dynamic_pointer_cast <lambda_p_llvm::context> (nodes [statement->association->references [1]]));
		check_binder (context, 1, L"context", problems);
		if (problems.errors.empty ())
		{
			boost::shared_ptr <lambda_p_llvm::module> module (new lambda_p_llvm::module (new llvm::Module (adata->string, context->context_m)));
			nodes [statement->association->declarations [0]] = module;
		}
	}
}

std::wstring lambda_p_llvm::module_binder::binder_name ()
{
	return std::wstring (L"module_binder");
}