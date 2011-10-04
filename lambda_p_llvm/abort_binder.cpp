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

void lambda_p_llvm::abort_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_count (0, 0, statement, problems);
	if (problems.empty ())
	{
        ::llvm::CallInst * call = ::llvm::CallInst::Create (abort_function);
        context->block->getInstList ().push_back (call);
    }
}

::std::wstring lambda_p_llvm::abort_binder::binder_name ()
{
	return ::std::wstring (L"abort_binder");
}