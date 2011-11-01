//
//  wprintf_function.h
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/20/11.
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
    class wprintf_function
    {
    public:
        wprintf_function (lambda_p_llvm::generation_context & context_a);
        llvm::Function * wprintf;
    };
}
