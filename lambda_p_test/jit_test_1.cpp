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

#include <vector>
#include <iostream>

#include <boost/array.hpp>

void lambda_p_test::jit_test_1::run ()
{
    run_1 ();
    run_2 ();
}

void lambda_p_test::jit_test_1::run_2 ()
{    
    ::llvm::LLVMContext context;
    ::llvm::StringRef name ("test");
    ::llvm::Module module (name, context);
    ::llvm::FunctionType * generation_type (::llvm::FunctionType::get (::llvm::Type::getVoidTy (context), false));
    ::llvm::Function * generation = ::llvm::Function::Create (generation_type, ::llvm::GlobalValue::ExternalLinkage);   
	module.getFunctionList ().push_back (generation);
    ::std::vector < ::llvm::Type const *> parameters;
    parameters.push_back (::llvm::PointerType::get (::llvm::Type::getInt8Ty (context), 0));
    parameters.push_back (::llvm::PointerType::get (::llvm::Type::getInt32Ty (context), 0));
    ::llvm::FunctionType * print_type (::llvm::FunctionType::get (::llvm::Type::getInt32Ty (context), parameters, false)); 
    ::llvm::Function * print = ::llvm::Function::Create (print_type, ::llvm::GlobalValue::ExternalLinkage);
	module.getFunctionList ().push_back (print);
    ::llvm::GlobalVariable * strptr = new ::llvm::GlobalVariable (::llvm::PointerType::get (::llvm::Type::getInt32Ty (context), 0), false, ::llvm::GlobalValue::ExternalLinkage);
	module.getGlobalList ().push_back (strptr);
    ::llvm::GlobalVariable * stderrptr = new ::llvm::GlobalVariable (::llvm::PointerType::get (::llvm::Type::getInt8Ty (context), 0), false, ::llvm::GlobalValue::ExternalLinkage);
	module.getGlobalList ().push_back (stderrptr);
    ::llvm::BasicBlock * block = ::llvm::BasicBlock::Create (context);
    generation->getBasicBlockList ().push_back (block);
    ::std::vector < ::llvm::Value *> arguments;
    ::llvm::LoadInst * load = new ::llvm::LoadInst (stderrptr);
    block->getInstList ().push_back (load);
    arguments.push_back (load);
	//arguments.push_back (stderrptr);
    ::llvm::LoadInst * load2 = new ::llvm::LoadInst (strptr);
    block->getInstList ().push_back (load2);
    arguments.push_back (load2);
	//arguments.push_back (strptr);
    ::llvm::CallInst * call (::llvm::CallInst::Create (print, arguments.begin (), arguments.end ()));
    block->getInstList ().push_back (call);
    ::llvm::ReturnInst * ret (::llvm::ReturnInst::Create (context));
    block->getInstList ().push_back (ret);
    assert (generation->getBasicBlockList ().size () == 1);
    assert (generation->getBasicBlockList ().begin ()->getInstList ().size () == 4);
    ::llvm::InitializeNativeTarget ();
    ::llvm::EngineBuilder builder (&module);
    builder.setEngineKind (::llvm::EngineKind::JIT);
    ::std::string error;
    builder.setErrorStr (&error);
    ::llvm::ExecutionEngine * engine = builder.create ();
    ::std::vector < ::llvm::GenericValue> arg_values;
    wchar_t const * str = L"test";
    engine->addGlobalMapping (strptr, &str);
    engine->addGlobalMapping (print, (void *)::fwprintf);
	FILE * err = stderr;
    engine->addGlobalMapping (stderrptr, &err);
    engine->runFunction (generation, arg_values);   
}

void lambda_p_test::jit_test_1::run_1 ()
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