//
//  llvm_generation_context.h
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/17/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <llvm/LLVMContext.h>

namespace llvm
{
    class BasicBlock;
    class Module;
    class IntegerType;
}
namespace lambda_p_llvm
{
    class generation_context
    {
    public:
        generation_context (::llvm::LLVMContext & context_a, ::llvm::Module * module_a, ::llvm::BasicBlock * block_a);
        ::llvm::LLVMContext & context;
        ::llvm::IntegerType const * wchar_t_type;
		::llvm::IntegerType const * size_t_type;
        ::llvm::Module * module;
        ::llvm::BasicBlock * block;
    };
}