#include "overlayed_functions.h"


#include <llvm/Module.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>

lambda_p_repl::overlayed_functions::overlayed_functions (llvm::Module * module, boost::shared_ptr <lambda_p_llvm::generation_context> context, llvm::ExecutionEngine * engine)
    : wprintf (*context),
     malloc (*context),
     memcpy (*context),
	 abort (*context)
{
    module->getFunctionList ().push_back (wprintf.wprintf);
    engine->addGlobalMapping (wprintf.wprintf, (void *)::wprintf);
    module->getFunctionList ().push_back (malloc.malloc);
    engine->addGlobalMapping (malloc.malloc, (void *)::malloc);
    module->getFunctionList ().push_back (memcpy.memcpy);
	engine->addGlobalMapping (abort.abort, (void *)::abort);
	module->getFunctionList ().push_back (abort.abort);
}