#include "overlayed_functions.h"

#include <lambda_p_llvm/generation_context.h>

#include <llvm/Module.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/DerivedTypes.h>

lambda_p_repl::overlayed_functions::overlayed_functions (llvm::Module * module, boost::shared_ptr <lambda_p_llvm::generation_context> context, llvm::ExecutionEngine * engine)
	: wprintf (context->context, context->wchar_t_type),
	malloc (context->context, context->size_t_type),
	memcpy (context->context),
	abort (context->context)
{
	module->getFunctionList ().push_back (wprintf.wprintf);
    engine->addGlobalMapping (wprintf.wprintf, (void *)::wprintf);
    module->getFunctionList ().push_back (malloc.malloc);
    engine->addGlobalMapping (malloc.malloc, (void *)::malloc);
    module->getFunctionList ().push_back (memcpy.memcpy);
	engine->addGlobalMapping (abort.abort, (void *)::abort);
	module->getFunctionList ().push_back (abort.abort);
}