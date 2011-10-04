//
//  abort_binder.cpp
//  lambda_p_repl
//
//  Created by Colin LeMahieu on 9/17/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p_llvm/abort_binder.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/statement.h>

#include <sstream>

#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>
#include <llvm/Function.h>

lambda_p_llvm::abort_binder::abort_binder (::llvm::Function * abort_function_a, ::lambda_p_llvm::generation_context * context_a)
: abort_function (abort_function_a),
context (context_a)
{
}

void lambda_p_llvm::abort_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	bool problem (false);
	check_count (problem, 0, 0, L"abort_binder", statement, problems);
	if (!problem)
	{
        ::llvm::CallInst * call = ::llvm::CallInst::Create (abort_function);
        context->block->getInstList ().push_back (call);
    }
}