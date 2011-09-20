//
//  wprintf_function.h
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <llvm/Value.h>

#include <lambda_p_llvm/llvm_generation_context.h>

namespace lambda_p_llvm
{
    class wprintf_function
    {
    public:
        wprintf_function (::lambda_p_llvm::llvm_generation_context context_a);
        ::llvm::Function * wprintf;
    };
}
