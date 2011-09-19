//
//  llvm_value.h
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p/binder/node_instance.h>

#include <llvm/Value.h>

namespace lambda_p_llvm
{
    class llvm_value : public ::lambda_p::binder::node_instance
    {
    public:  
        llvm_value (::llvm::Value * value_a);
        ::llvm::Value * value;
        void operator () ();
    };
}
