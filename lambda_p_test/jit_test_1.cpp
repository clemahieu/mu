//
//  jit_test_1.cpp
//  lambda_p_test
//
//  Created by Colin LeMahieu on 9/17/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p_test/jit_test_1.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Target/TargetSelect.h>
#include <llvm/Instructions.h>

void lambda_p_test::jit_test_1::run ()
{
    ::llvm::LLVMContext context;
    ::llvm::StringRef name ("test");
    ::llvm::Module module (name, context);
    ::llvm::FunctionType * type (::llvm::FunctionType::get (::llvm::Type::getVoidTy (context), false));
    ::llvm::Function * generation = ::llvm::Function::Create (type, ::llvm::GlobalValue::ExternalLinkage);   
    module.getFunctionList ().push_back (generation);
    ::llvm::BasicBlock * block = ::llvm::BasicBlock::Create (context);
    generation->getBasicBlockList ().push_back (block);
    ::llvm::ReturnInst * ret (::llvm::ReturnInst::Create (context));
    block->getInstList ().push_back (ret);
    assert (generation->getBasicBlockList ().size () == 1);
    assert (generation->getBasicBlockList ().begin ()->getInstList ().size () == 1);
    ::llvm::InitializeNativeTarget ();
    ::llvm::EngineBuilder builder (&module);
    builder.setEngineKind (::llvm::EngineKind::JIT);
    ::std::string error;
    builder.setErrorStr (&error);
    ::llvm::ExecutionEngine * engine = builder.create ();
    ::std::vector < ::llvm::GenericValue> arg_values;
    engine->runFunction (generation, arg_values);
}