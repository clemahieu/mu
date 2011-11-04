#include "overlay_binder.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/execution_engine.h>
#include <lambda_p_kernel/package.h>
#include <lambda_p_llvm/module.h>
#include <lambda_p_llvm/abort_function.h>
#include <lambda_p_llvm/malloc_function.h>
#include <lambda_p_llvm/memcpy_function.h>
#include <lambda_p_llvm/wprintf_function.h>
#include <lambda_p_llvm/fo_value.h>
#include <lambda_p/binder/node_list.h>

#include <llvm/Module.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>

void lambda_p_llvm::overlay_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (0, 2, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_llvm::execution_engine> engine (boost::dynamic_pointer_cast <lambda_p_llvm::execution_engine> (nodes [statement->association->references [0]]));
		check_binder (engine, 0, L"execution_engine", problems);
		boost::shared_ptr <lambda_p_llvm::module> module (boost::dynamic_pointer_cast <lambda_p_llvm::module> (nodes [statement->association->references [1]]));
		check_binder (module, 1, L"module", problems);
		if (problems.errors.empty ())
		{
			llvm::Function * abort (module->module_m->getFunction (llvm::StringRef ("abort")));
			if (abort != nullptr)
			{
				engine->engine->addGlobalMapping (abort, (void *)::abort);
			}
			llvm::Function * malloc (module->module_m->getFunction (llvm::StringRef ("malloc")));
			if (malloc != nullptr)
			{
				engine->engine->addGlobalMapping (malloc, (void *)::malloc);
			}
			llvm::Function * wprintf (module->module_m->getFunction (llvm::StringRef ("wprintf")));
			if (wprintf != nullptr)
			{
				engine->engine->addGlobalMapping (wprintf, (void *)::wprintf);
			}
		}
	}
}

std::wstring lambda_p_llvm::overlay_binder::binder_name ()
{
	return std::wstring (L"overlay_binder");
}