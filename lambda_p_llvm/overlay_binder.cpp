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

lambda_p_llvm::overlay_binder::overlay_binder (llvm::Type const * size_t_type_a, llvm::Type const * wchar_t_type_a)
	: size_t_type (size_t_type_a),
	wchar_t_type (wchar_t_type_a)
{
}

void lambda_p_llvm::overlay_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_llvm::execution_engine> engine (boost::dynamic_pointer_cast <lambda_p_llvm::execution_engine> (nodes [statement->association->references [0]]));
		if (engine.get () != nullptr)
		{
			boost::shared_ptr <lambda_p_llvm::module> module (boost::dynamic_pointer_cast <lambda_p_llvm::module> (nodes [statement->association->references [1]]));
			if (module.get () != nullptr)
			{
				boost::shared_ptr <lambda_p_kernel::package> package (new lambda_p_kernel::package);
				lambda_p_llvm::abort_function abort (module->module_m->getContext ());
				module->module_m->getFunctionList ().push_back (abort.abort);
				engine->engine->addGlobalMapping (abort.abort, (void *)::abort);
				package->nodes [std::wstring (L"abort")] = boost::shared_ptr <lambda_p_llvm::fo_value> (new lambda_p_llvm::fo_value (abort.abort));
				lambda_p_llvm::malloc_function malloc (module->module_m->getContext (), size_t_type);
				module->module_m->getFunctionList ().push_back (malloc.malloc);
				engine->engine->addGlobalMapping (malloc.malloc, (void *)::malloc);
				package->nodes [std::wstring (L"malloc")] = boost::shared_ptr <lambda_p_llvm::fo_value> (new lambda_p_llvm::fo_value (malloc.malloc));
				lambda_p_llvm::memcpy_function memcpy (module->module_m->getContext ());
				module->module_m->getFunctionList ().push_back (memcpy.memcpy);
				engine->engine->addGlobalMapping (memcpy.memcpy, (void *)::memcpy);
				package->nodes [std::wstring (L"memcpy")] = boost::shared_ptr <lambda_p_llvm::fo_value> (new lambda_p_llvm::fo_value (memcpy.memcpy));
				lambda_p_llvm::wprintf_function wprintf (module->module_m->getContext (), wchar_t_type);
				module->module_m->getFunctionList ().push_back (wprintf.wprintf);
				engine->engine->addGlobalMapping (wprintf.wprintf, (void *)::wprintf);
				package->nodes [std::wstring (L"wprintf")] = boost::shared_ptr <lambda_p_llvm::fo_value> (new lambda_p_llvm::fo_value (wprintf.wprintf));
				nodes [statement->association->declarations [0]] = package;
			}
		}
		else
		{
			unexpected_binder_type_error (0, L"engine", problems);
		}
	}
}

std::wstring lambda_p_llvm::overlay_binder::binder_name ()
{
	return std::wstring (L"overlay_binder");
}