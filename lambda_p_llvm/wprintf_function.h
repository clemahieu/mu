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
	class LLVMContext;
	class Type;
}
namespace lambda_p_llvm
{
	class generation_context;
    class wprintf_function
    {
    public:
        wprintf_function (llvm::LLVMContext & context_a, llvm::Type const * wchar_t_type);
        llvm::Function * wprintf;
    };
}
