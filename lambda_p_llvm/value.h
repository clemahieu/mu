//
//  llvm_value.h
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p/binder/node.h>

#include <llvm/Value.h>

namespace lambda_p_llvm
{
    class value : public lambda_p::binder::node
    {
    public:  
        virtual llvm::Value * operator () () = 0;
		virtual llvm::Type const * type () = 0;
    };
}
