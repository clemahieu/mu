//
//  echo_binder_test.cpp
//  lambda_p_test
//
//  Created by Colin LeMahieu on 9/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p_test/echo_binder_test.h>

#include <lambda_p_repl/echo_binder.h>
#include <lambda_p_llvm/llvm_generation_context.h>
#include <lambda_p_llvm/wprintf_function.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>

#include <llvm/LLVMContext.h>
#include <llvm/Function.h>

void lambda_p_test::echo_binder_test::run ()
{
    ::llvm::LLVMContext llvm_context;
    ::lambda_p_llvm::llvm_generation_context context (llvm_context);
    ::lambda_p_llvm::wprintf_function wprintf (context);
    ::lambda_p_repl::echo_binder binder (wprintf.wprintf, context);
    ::lambda_p::core::routine routine;
    ::lambda_p::core::statement * parameters = routine.add_statement ();
    ::lambda_p::core::declaration * p1 = routine.add_declaration (0, 0);
    parameters->add_argument (p1);
}