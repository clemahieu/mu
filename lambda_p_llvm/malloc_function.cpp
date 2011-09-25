#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "malloc_function.h"

#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>

lambda_p_llvm::malloc_function::malloc_function (::lambda_p_llvm::generation_context context_a)
{
	::std::vector < ::llvm::Type const *> malloc_arguments;
	malloc_arguments.push_back (context_a.size_t_type);
	::llvm::FunctionType * malloc_type (::llvm::FunctionType::get (::llvm::Type::getInt8PtrTy (context_a.context), malloc_arguments, false));
	malloc = ::llvm::Function::Create (malloc_type, ::llvm::GlobalValue::ExternalLinkage);
}

lambda_p_llvm::malloc_function::~malloc_function (void)
{
}