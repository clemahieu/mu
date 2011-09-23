//
//  llvm_generation_context.cpp
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/17/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p_llvm/generation_context.h>

#include <llvm/Type.h>
#include <llvm/DerivedTypes.h>

#include <assert.h>

lambda_p_llvm::generation_context::generation_context (::llvm::LLVMContext & context_a, ::llvm::Module * module_a, ::llvm::BasicBlock * block_a)
: context (context_a),
module (module_a),
block (block_a)
{
	size_t wchar_t_size (sizeof (wchar_t) * 8);
	wchar_t_type = ::llvm::IntegerType::get (context_a, wchar_t_size);
	size_t size_t_size (sizeof (size_t) * 8);
	size_t_type = ::llvm::IntegerType::get (context_a, size_t_size);	
}