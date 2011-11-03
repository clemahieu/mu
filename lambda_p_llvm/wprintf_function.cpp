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
#include <lambda_p_llvm/generation_context.h>

#include <llvm/DerivedTypes.h>
#include <llvm/GlobalValue.h>
#include <llvm/Function.h>

lambda_p_llvm::wprintf_function::wprintf_function (llvm::LLVMContext & context_a, llvm::Type const * wchar_t_type)
{    
    std::vector <llvm::Type const *> wprintf_parameters;
    wprintf_parameters.push_back (llvm::PointerType::get (wchar_t_type, 0));
    llvm::FunctionType * wprintf_type (llvm::FunctionType::get (llvm::Type::getInt32Ty (context_a), wprintf_parameters, true));
    wprintf = llvm::Function::Create (wprintf_type, llvm::GlobalValue::ExternalLinkage, llvm::Twine ("wprintf"));
}