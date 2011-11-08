//
//  llvm_value.h
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p/binder/node.h>

namespace llvm
{
	class Value;
	class Type;
}
namespace lambda_p_llvm
{
    class value : public lambda_p::binder::node
    {
    public:  
		value (llvm::Value * value_a);
        llvm::Value * operator () ();
		llvm::Type const * type ();
		llvm::Value * value_m;
    };
}
