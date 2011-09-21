//
//  wprintf_function.cpp
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p_llvm/wprintf_function.h>

#include <llvm/DerivedTypes.h>
#include <llvm/GlobalValue.h>
#include <llvm/Function.h>

lambda_p_llvm::wprintf_function::wprintf_function (::lambda_p_llvm::generation_context context_a)
{    
    ::std::vector < ::llvm::Type const *> wprintf_parameters;
    wprintf_parameters.push_back (::llvm::PointerType::get (context_a.wchar_t_type, 0));
    ::llvm::FunctionType * wprintf_type (::llvm::FunctionType::get (::llvm::Type::getInt32Ty (context_a.context), wprintf_parameters, true));
    wprintf = ::llvm::Function::Create (wprintf_type, ::llvm::GlobalValue::ExternalLinkage);
}