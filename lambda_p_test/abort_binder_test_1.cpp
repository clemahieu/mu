//
//  abort_binder_test_1.cpp
//  lambda_p_test
//
//  Created by Colin LeMahieu on 9/17/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p_test/abort_binder_test_1.h>
#include <lambda_p_llvm/abort_binder.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/abort_function.h>
#include <lambda_p/errors/error_list.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Target/TargetSelect.h>
#include <llvm/Instructions.h>

#include <sstream>
#include <vector>

void lambda_p_test::abort_binder_test_1::run ()
{
    llvm::LLVMContext context;
    llvm::StringRef name ("test");
    llvm::Module * module (new llvm::Module (name, context));
    lambda_p_llvm::generation_context current (context, module, nullptr);
	lambda_p_llvm::abort_function abort_function (current);
	llvm::Function * generation = llvm::Function::Create (abort_function.abort->getFunctionType (), llvm::GlobalValue::ExternalLinkage);   
    module->getFunctionList ().push_back (abort_function.abort);
    module->getFunctionList ().push_back (generation);
    llvm::BasicBlock * block = llvm::BasicBlock::Create (context);
    generation->getBasicBlockList ().push_back (block);
    current.block = block;
	lambda_p_llvm::abort_binder binder (abort_function.abort, &current);
    lambda_p::core::routine routine;
    size_t parameter (routine.add_declaration ());
	routine.surface->declarations.push_back (parameter);
    lambda_p::core::statement * call (routine.add_statement ());
	call->target = parameter;
    lambda_p::binder::node_list nodes;
	lambda_p::errors::error_list problems;
    binder.bind (call, nodes, problems);
    llvm::ReturnInst * ret (llvm::ReturnInst::Create (context));
    block->getInstList ().push_back (ret);
	assert (problems.errors.size () == 0);
    assert (generation->getBasicBlockList ().size () == 1);
    assert (generation->getBasicBlockList ().begin ()->getInstList ().size () == 2);
}