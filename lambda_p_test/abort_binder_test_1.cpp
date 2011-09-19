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
#include <lambda_p_llvm/llvm_generation_context.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/routine.h>

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
    ::llvm::LLVMContext context;
    ::lambda_p_llvm::llvm_generation_context current (context);
    ::llvm::StringRef name ("test");
    ::llvm::Module module (name, context);
    ::llvm::FunctionType * type (::llvm::FunctionType::get (::llvm::Type::getVoidTy (context), false));
    ::llvm::Function * function = ::llvm::Function::Create (type, ::llvm::GlobalValue::ExternalLinkage);
    ::llvm::Function * generation = ::llvm::Function::Create (type, ::llvm::GlobalValue::ExternalLinkage);   
    module.getFunctionList ().push_back (function);
    module.getFunctionList ().push_back (generation);
    ::llvm::BasicBlock * block = ::llvm::BasicBlock::Create (context);
    generation->getBasicBlockList ().push_back (block);
    current.block = block;
    ::lambda_p_llvm::abort_binder binder (function, &current);
    ::lambda_p::core::routine routine;
    ::lambda_p::core::statement * statement (routine.add_statement ());
    ::lambda_p::core::declaration * parameter (routine.add_declaration (0, 0));
    statement->add_argument (parameter);
    ::lambda_p::core::statement * call (routine.add_statement ());
    ::lambda_p::core::reference * target (routine.add_reference (0, 0, 1, 0));
    call->add_argument (target);
    ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > instances;
    ::std::wstringstream problems;
    binder.bind (call, instances, problems);
    ::llvm::ReturnInst * ret (::llvm::ReturnInst::Create (context));
    block->getInstList ().push_back (ret);
    assert (problems.str ().size () == 0);
    assert (generation->getBasicBlockList ().size () == 1);
    assert (generation->getBasicBlockList ().begin ()->getInstList ().size () == 2);
}