#include "abort_function.h"

#include <lambda_p_llvm/generation_context.h>

#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>

lambda_p_repl::abort_function::abort_function (lambda_p_llvm::generation_context & context_a)
{
    llvm::FunctionType * type (llvm::FunctionType::get (llvm::Type::getVoidTy (context_a.context), false));
    abort = llvm::Function::Create (type, llvm::GlobalValue::ExternalLinkage);
}

