#include "api_test.h"

#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_repl/api.h>
#include <lambda_p_llvm/malloc_function.h>
#include <lambda_p_llvm/memcpy_function.h>
#include <lambda_p_llvm/wprintf_function.h>
#include <lambda_p_llvm/abort_function.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>

void lambda_p_test::api_test::run ()
{
	run_1 ();
}

void lambda_p_test::api_test::run_1 ()
{
	llvm::LLVMContext context_item;
	llvm::Module * module (new llvm::Module (llvm::StringRef ("test"), context_item));
	llvm::Function * function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context_item), false), llvm::GlobalValue::ExternalLinkage));
	module->getFunctionList ().push_back (function);
	llvm::BasicBlock * block (llvm::BasicBlock::Create (context_item));
	function->getBasicBlockList ().push_back (block);
	lambda_p_llvm::generation_context context (context_item, module, block);
	lambda_p_llvm::malloc_function malloc_function (context);
	lambda_p_llvm::memcpy_function memcpy_function (context);
	lambda_p_llvm::wprintf_function wprintf_function (context);
	lambda_p_llvm::abort_function abort_function (context);
	llvm::EngineBuilder builder (module);
    builder.setEngineKind (llvm::EngineKind::JIT);
    std::string error;
    builder.setErrorStr (&error);
	llvm::ExecutionEngine * engine (builder.create ());
	lambda_p_repl::api api (engine, context, wprintf_function, malloc_function, abort_function, memcpy_function);
	assert (api.package.get () != nullptr);
}