//
//  llvmcontext.cpp
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/15/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p_llvm/llvm_context.h>

void lambda_p_llvm::llvm_context::operator () ()
{
	context.reset (new ::llvm::LLVMContext);
}