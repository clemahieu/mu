//
//  memcpy_function.h
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

namespace llvm
{
    class Function;
}
namespace lambda_p_llvm
{
    class generation_context;
    class memcpy_function
    {
    public:
        memcpy_function (lambda_p_llvm::generation_context & context_a);
        llvm::Function * memcpy;
    };
}