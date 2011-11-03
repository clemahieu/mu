#include "overlay_binder.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/execution_engine.h>
#include <lambda_p/binder/node_list.h>

#include <llvm/Module.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>

void lambda_p_llvm::overlay_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (0, 1, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_llvm::execution_engine> engine (boost::dynamic_pointer_cast <lambda_p_llvm::execution_engine> (nodes [statement->association->references [0]]));
		if (engine.get () != nullptr)
		{
			//llvm::Function * abort (engine->engine->module->module_m->getFunction (llvm::StringRef ("abort")));
			//if (abort != nullptr)
			//{
			//	engine->addGlobalMapping (abort, (void *)::abort);
			//}
			//llvm::Function * malloc (module->module_m->getFunction (llvm::StringRef ("malloc")));
			//if (malloc != nullptr)
			//{
			//	engine->addGlobalMapping (malloc, (void *)::malloc);
			//}
			//llvm::Function * memcpy (module->module_m->getFunction (llvm::StringRef ("memcpy")));
			//if (memcpy != nullptr)
			//{
			//	engine->addGlobalMapping (memcpy, (void *)::memcpy);
			//}
			//llvm::Function * wprintf (module->module_m->getFunction (llvm::StringRef ("wprintf")));
			//if (wprintf != nullptr)
			//{
			//	engine->addGlobalMapping (wprintf, (void *)::wprintf);
			//}
		}
		else
		{
			unexpected_binder_type_error (0, L"module", problems);
		}
	}
}

std::wstring lambda_p_llvm::overlay_binder::binder_name ()
{
	return std::wstring (L"overlay_binder");
}