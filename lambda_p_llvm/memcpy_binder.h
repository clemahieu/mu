//
//  memcpy_binder.h
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <lambda_p/binder/node_binder.h>

namespace llvm
{
    class Function;
}
namespace lambda_p_llvm
{
    class generation_context;
    class memcpy_binder : public ::lambda_p::binder::node_binder
    {
    public:
        memcpy_binder (::lambda_p_llvm::generation_context & context_a, ::llvm::Function * memcpy_function);
        void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems);
    private:
        ::llvm::Function * memcpy_function;
        ::lambda_p_llvm::generation_context & context;
    };
}