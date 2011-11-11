#include "verify_binder.h"

#include <lambda_p/binder/binder_implementor.h>
#include <lambda_p_llvm/module.h>

#include <llvm/Analysis/Verifier.h>
#include <llvm/Module.h>

void lambda_p_llvm::verify_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (0, 1, statement, problems);
	if (problems.errors.empty ())
	{
		auto module (boost::dynamic_pointer_cast <lambda_p_llvm::module> (nodes [statement->association->references [0]]));
		check_binder (module, 0, L"module", problems);
		if (problems.errors.empty ())
		{
			std::string error_info;
			auto error (llvm::verifyModule (*module->module_m, llvm::VerifierFailureAction::ReturnStatusAction, &error_info));
			if (error)
			{
				std::wstring message (error_info.begin (), error_info.end ());
				add_error (message, problems);
			}
		}
	}
}

std::wstring lambda_p_llvm::verify_binder::binder_name ()
{
	return std::wstring (L"verify_binder");
}