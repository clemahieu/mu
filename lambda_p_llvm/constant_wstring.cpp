//
//  constant_wstring.cpp
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p_llvm/constant_wstring.h>
#include <lambda_p_llvm/generation_context.h>

#include <llvm/DerivedTypes.h>
#include <llvm/Constants.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Module.h>

lambda_p_llvm::constant_wstring::constant_wstring (lambda_p_llvm::generation_context & context, std::wstring const & string)
{    
    llvm::ArrayType * string_type (llvm::ArrayType::get (context.wchar_t_type, string.size () + 1));
    std::vector < llvm::Constant *> string_initializer;
    for (std::wstring::const_iterator i = string.begin (); i != string.end (); ++i)
    {
        string_initializer.push_back (llvm::ConstantInt::get (context.wchar_t_type, *i));
    }
    string_initializer.push_back (llvm::ConstantInt::get (context.wchar_t_type, 0));
    llvm::Constant * string_array (llvm::ConstantArray::get (string_type, string_initializer));
    llvm::GlobalVariable * string_global (new llvm::GlobalVariable (string_type, true, llvm::GlobalValue::ExternalLinkage, string_array));
    context.module->getGlobalList ().push_back (string_global);
    value = llvm::ConstantExpr::getPointerCast (string_global, llvm::PointerType::get (context.wchar_t_type, 0));
}