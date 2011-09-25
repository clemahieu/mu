//
//  memcpy_function.cpp
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/memcpy_function.h>

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/ADT/Twine.h>

lambda_p_llvm::memcpy_function::memcpy_function (::lambda_p_llvm::generation_context & context_a)
{
    ::std::vector < ::llvm::Type const *> memcpy_parameters;
    memcpy_parameters.push_back (::llvm::Type::getInt8PtrTy (context_a.context));
    memcpy_parameters.push_back (::llvm::Type::getInt8PtrTy (context_a.context));
    memcpy_parameters.push_back (::llvm::Type::getInt64Ty (context_a.context));
    memcpy_parameters.push_back (::llvm::Type::getInt32Ty (context_a.context));
    memcpy_parameters.push_back (::llvm::Type::getInt1Ty (context_a.context));
    ::llvm::FunctionType * memcpy_type (::llvm::FunctionType::get (::llvm::Type::getVoidTy (context_a.context), memcpy_parameters, false));
    ::llvm::Twine name ("llvm.memcpy.p0i8.p0i8.i64");
    memcpy = ::llvm::Function::Create (memcpy_type, ::llvm::GlobalValue::ExternalLinkage, name);
}