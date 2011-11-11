#include "compile.h"

#include <lambda_p/binder/binder_implementor.h>
#include <lambda_p_llvm/module.h>
#include <lambda_p_kernel/adata.h>

#include <llvm/Target/TargetRegistry.h>
#include <llvm/Support/Host.h>

void lambda_p_llvm::compile::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (0, 2, statement, problems);
	if (problems.errors.empty ())
	{
		auto module (boost::dynamic_pointer_cast <lambda_p_llvm::module> (nodes [statement->association->references [0]]));
		check_binder (module, 0, L"module", problems);
		auto name (boost::dynamic_pointer_cast <lambda_p_kernel::adata> (nodes [statement->association->references [1]]));
		check_binder (name, 1, L"adata", problems);
		if (problems.errors.empty ())
		{
			std::string error;
			llvm::Target const * target (llvm::TargetRegistry::lookupTarget (llvm::sys::getHostTriple (), error));
			if (error.empty ())
			{

			}
			else
			{
				std::wstring message (error.begin (), error.end ());
				add_error (message.str (), problems);
			}
		}
	}
}

std::wstring lambda_p_llvm::compile::binder_name ()
{
	return std::wstring (L"compile");
}