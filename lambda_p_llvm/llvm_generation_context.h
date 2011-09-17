//
//  llvm_generation_context.h
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/17/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

namespace llvm
{
    class BasicBlock;
}
namespace lambda_p_llvm
{
    class llvm_generation_context
    {
    public:
        ::llvm::BasicBlock * block;
    };
}