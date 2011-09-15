//
//  llvmcontext.h
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/15/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p/binder/node_instance.h>

#include <llvm/LLVMContext.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p_llvm
{
	class llvm_context : public ::lambda_p::binder::node_instance
    {
		void operator () ();
		::boost::shared_ptr < ::llvm::LLVMContext> context;		
    };
}